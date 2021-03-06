// PDE_1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

using namespace std;

float forward_difference_scheme(int a, float k, float h, float u_n_j, float u_n_jplusone);
float backward_difference_scheme(int a, float k, float h, float u_n_j, float u_n_jminusone);
float central_difference_scheme(int a, float k, float h, float u_n_j, float u_n_jplusone, float u_n_jminusone);

int main()
{
	ofstream out;

	float a = -2;
	
	float time_start	= 0;
	float time_end		= 0.25;

	float space_start	= -2;
	float space_end		=  2;

	int		num_space_nodes	= 200;
	float	k_step			= 0.005;

	int num_time_nodes = (time_end - time_start) / k_step + 1;
	float x_step = (space_end - space_start) / num_space_nodes;
	num_space_nodes++;

	float** u = new float* [num_time_nodes];
	for (int i = 0; i < num_time_nodes; i++)
		u[i] = new float [num_space_nodes];

	for (int i = 0; i < num_space_nodes; i++)
		u[0][i] = sin(M_PI * ((float)space_start + i * x_step));

//////////////////////////////////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < num_time_nodes - 1; i++)
	{
		for (int j = 0; j < num_space_nodes - 1; j++)
			u[i + 1][j] = forward_difference_scheme(a, k_step, x_step, u[i][j], u[i][j + 1]);

		u[i + 1][num_space_nodes - 1] = u[i + 1][0];
	}

	
	out.open("forward_diff_scheme.txt");
	for (int i = 0; i < num_space_nodes; i++)
		out << u[num_time_nodes - 1][i] << "\n";
	out.close();
	cout << "forward_diff_scheme done\n";

//////////////////////////////////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < num_space_nodes; i++)
		u[0][i] = sin(M_PI * ((float)space_start + i * x_step));

	for (int i = 0; i < num_time_nodes - 1; i++)
	{
		for (int j = 1; j < num_space_nodes - 1; j++)
			u[i + 1][j] = central_difference_scheme(a, k_step, x_step, u[i][j], u[i][j + 1], u[i][j - 1]);
	}

	out.open("central_diff_scheme.txt");
	for (int i = 0; i < num_space_nodes; i++)
		out << u[num_time_nodes - 1][i] << '\n';
	out.close();
	cout << "central_diff_scheme done\n";

//////////////////////////////////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < num_time_nodes - 1; i++)
	{
		for (int j = 1; j < num_space_nodes; j++)
			u[i + 1][j] = backward_difference_scheme(a, k_step, x_step, u[i][j - 1], u[i][j]);

		u[i + 1][0] = u[i + 1][num_space_nodes - 1];
	}

	out.open("backward_diff_scheme.txt");
	for (int i = 0; i < num_space_nodes; i++)
		out << u[num_time_nodes - 1][i] << "\n";
	out.close();
	cout << "backward_diff_scheme done\n";

	_getch();

    return 0;
}

float forward_difference_scheme(int a, float k, float h, float u_n_j, float u_n_jplusone)
{
	return u_n_j - a * (k / h) * (u_n_jplusone - u_n_j);
}


float backward_difference_scheme(int a, float k, float h, float u_n_j, float u_n_jminusone)
{
	return u_n_j - a * (k / h) * (u_n_j - u_n_jminusone);
}


float central_difference_scheme(int a, float k, float h, float u_n_j, float u_n_jplusone, float u_n_jminusone)
{
	return u_n_j - a * (k / (2 * h)) * (u_n_jplusone - u_n_jminusone);
}
