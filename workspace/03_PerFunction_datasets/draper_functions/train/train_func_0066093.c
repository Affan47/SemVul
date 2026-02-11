dw_pval (const gretl_matrix *u, const gretl_matrix *X,
		double *pDW, int *perr)
{
    gretl_matrix *M = NULL;
    gretl_matrix *A = NULL;
    gretl_matrix *MA = NULL;
    gretl_matrix *XX = NULL;
    gretl_matrix *E = NULL;
    double uu, DW;
    double pv = NADBL;
    int k = X->cols;
    int n = X->rows;
    int i, err = 0;

    M = gretl_identity_matrix_new(n);
    A = gretl_DW_matrix_new(n);
    MA = gretl_matrix_alloc(n, n);
    XX = gretl_matrix_alloc(k, k);

    if (M == NULL || A == NULL || MA == NULL || XX == NULL) {
	err = E_ALLOC;
	goto bailout;
    }

    gretl_matrix_multiply_mod(X, GRETL_MOD_TRANSPOSE,
			      X, GRETL_MOD_NONE,
			      XX, GRETL_MOD_NONE);

    err = gretl_invert_symmetric_matrix(XX);

    if (!err) {

	err = gretl_matrix_qform(X, GRETL_MOD_NONE,
				 XX, M, GRETL_MOD_DECREMENT);
    }

    if (!err) {
	err = gretl_matrix_multiply(M, A, MA);
    }

    if (!err) {
	uu = gretl_matrix_dot_product(u, GRETL_MOD_TRANSPOSE,
				      u, GRETL_MOD_NONE,
				      &err);
    }

    if (!err) {
	DW = gretl_scalar_qform(u, A, &err);
    }

    if (!err) {
	DW /= uu;
#if 0
	fprintf(stderr, "DW = %g\n", DW);
#endif
	E = gretl_general_matrix_eigenvals(MA, 0, &err);
    }

    if (!err) {
	k = n - k;
	for (i=0; i<k; i++) {
	    E->val[i] -= DW;
	}
	gretl_matrix_reuse(E, k, 1);
	pv = imhof(E, 0.0, &err);
	if (!err && pDW != NULL) {
	    *pDW = DW;
	}
    }

 bailout:

    gretl_matrix_free(M);
    gretl_matrix_free(A);
    gretl_matrix_free(MA);
    gretl_matrix_free(XX);
    gretl_matrix_free(E);

    *perr = err;

    return pv;
}
