disp_matrix(double **a, double *x, double *z, int n)


{

    int row, col;
    char dummy[128];

    for (row = 0; row < n; row++) {
	fprintf(stdout, "[ ");

	for (col = 0; col < n; col++)
	    fprintf(stdout, "%.3f\t", a[row][col] / 1);

	fprintf(stdout, "]\t[ %.0f\t]\t[ %.0f\t]\n", x[row], z[row]);
    }
    fprintf(stdout, "\n\n");

    fgets(dummy, 70, stdin);
}
