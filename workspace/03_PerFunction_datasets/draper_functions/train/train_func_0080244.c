xtxlag (gretl_matrix *wt, const gretl_matrix *X,
		    int n, int t, int lag)
{
    double xi, xj;
    int i, j;

    for (i=0; i<n; i++) {
	xi = gretl_matrix_get(X, t, i);
	for (j=0; j<n; j++) {
	    xj = gretl_matrix_get(X, t - lag, j);
	    gretl_matrix_set(wt, i, j, xi * xj);
	}
    }
}
