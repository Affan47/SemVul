copy_initial_hessian (gretl_matrix *A, double **H,
				 int n)
{
    int i, j;

#if BFGS_DEBUG
    gretl_matrix_print(A, "BFGS: initial Hessian inverse");
#endif

    if (gretl_is_null_matrix(A)) {
	for (i=0; i<n; i++) {
	    for (j=0; j<i; j++) {
		H[i][j] = 0.0;
	    }
	    H[i][i] = 1.0;
	}
    } else if (A->rows != n || A->cols != n) {
	return E_NONCONF;
    } else {
	for (i=0; i<n; i++) {
	    for (j=0; j<=i; j++) {
		H[i][j] = gretl_matrix_get(A, i, j);
	    }
	}
    }

    return 0;
}
