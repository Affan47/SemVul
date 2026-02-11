dGenXtrue(int n, int nrhs, double *x, int ldx)
{
    int  i, j;
    for (j = 0; j < nrhs; ++j)
	for (i = 0; i < n; ++i) {
	    x[i + j*ldx] = 1.0;
	}
}
