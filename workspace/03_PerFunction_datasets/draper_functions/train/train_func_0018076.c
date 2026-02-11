solve_cubic_2(tri_diag m[], double x[], int n)
{
    int i;
    double x_n;


    x_n = x[n - 1];
    for (i = 0; i < n - 2; i++) {
	x[i + 1] -= m[i][2] * x[i];
	x_n -= m[i][0] * x[i];
    }
    if (n >= 2)
	x[n - 1] = x_n - m[n - 2][0] * x[n - 2];


    for (i = 0; i < n; i++)
	x[i] /= m[i][1];


    x_n = x[n - 1];
    if (n >= 2)
	x[n - 2] -= m[n - 2][0] * x_n;
    for (i = n - 3; i >= 0; i--) {

	x[i] -= m[i][2] * x[i + 1] + m[i][0] * x_n;
    }
    return;
}
