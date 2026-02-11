real_xcf_vec (const double *x, const double *y,
				   int p, int T, int *err)
{
    gretl_matrix *xcf;
    double xbar, ybar;
    int i;

    xbar = gretl_mean(0, T-1, x);
    if (na(xbar)) {
	*err = E_DATA;
	return NULL;
    }

    ybar = gretl_mean(0, T-1, y);
    if (na(ybar)) {
	*err = E_DATA;
	return NULL;
    }

    xcf = gretl_column_vector_alloc(p * 2 + 1);
    if (xcf == NULL) {
	*err = E_ALLOC;
	return NULL;
    }

    for (i=-p; i<=p; i++) {
	xcf->val[i+p] = gretl_xcf(i, 0, T - 1, x, y, xbar, ybar);
    }

    return xcf;
}
