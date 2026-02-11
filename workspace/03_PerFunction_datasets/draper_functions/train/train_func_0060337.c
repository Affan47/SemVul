gretl_vector_from_array (const double *x, int n, GretlMatrixMod mod)
{
    gretl_matrix *v;
    double xi;

    v = gretl_column_vector_alloc(n);

    if (v != NULL) {
	int i = 0, j = 0;

	while (j < n) {
	    xi = x[i++];
	    if (!na(xi)) {
		if (mod == GRETL_MOD_SQUARE) {
		    v->val[j] = xi * xi;
		} else {
		    v->val[j] = xi;
		}
		j++;
	    }
	}
    }

    return v;
}
