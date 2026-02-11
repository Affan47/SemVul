gretl_blas_dsyrk (const gretl_matrix *a, int atr,
			      gretl_matrix *c, GretlMatrixMod cmod)
{
    char uplo = 'U';
    char tr = (atr)? 'T' : 'N';
    integer n = c->rows;
    integer k = (atr)? a->rows : a->cols;
    integer lda = a->rows;
    double x, alpha = 1.0, beta = 0.0;
#if defined(_OPENMP)
    guint64 fpm;
#endif
    int i, j;

    if (cmod == GRETL_MOD_CUMULATE) {
	beta = 1.0;
    } else if (cmod == GRETL_MOD_DECREMENT) {
	alpha = -1.0;
	beta = 1.0;
    }

    dsyrk_(&uplo, &tr, &n, &k, &alpha, a->val, &lda,
	   &beta, c->val, &n);

#if defined(_OPENMP)
    fpm = (guint64) n * n;
    if (!libset_use_openmp(fpm)) {
	goto st_mode;
    }
#pragma omp parallel for private(i, j, x)
    for (i=0; i<n; i++) {
	for (j=i+1; j<n; j++) {
	    x = gretl_matrix_get(c, i, j);
	    gretl_matrix_set(c, j, i, x);
	}
    }
    return;

   st_mode:
#endif

    for (i=0; i<n; i++) {
	for (j=i+1; j<n; j++) {
	    x = gretl_matrix_get(c, i, j);
	    gretl_matrix_set(c, j, i, x);
	}
    }
}
