gretl_LU_solve (gretl_matrix *a, gretl_matrix *b)
{
    char trans = 'N';
    integer info;
    integer n, ldb, nrhs = 1;
    integer *ipiv;
    int err = 0;

    if (gretl_is_null_matrix(a) ||
	gretl_is_null_matrix(b) ||
	a->rows != a->cols) {
	return E_DATA;
    }

    n = a->cols;

    if (b->cols == 1) {
	ldb = b->rows;
    } else if (b->rows == 1) {
	ldb = b->cols;
    } else {
	nrhs = b->cols;
	ldb = b->rows;
    }

    ipiv = malloc(n * sizeof *ipiv);
    if (ipiv == NULL) {
	return E_ALLOC;
    }

    dgetrf_(&n, &n, a->val, &n, ipiv, &info);

    if (info != 0) {
	fprintf(stderr, "gretl_LU_solve: dgetrf gave info = %d\n",
		(int) info);
	err = (info < 0)? E_DATA : E_SINGULAR;
    }

    if (!err) {
	dgetrs_(&trans, &n, &nrhs, a->val, &n, ipiv, b->val, &ldb, &info);
	if (info != 0) {
	    fprintf(stderr, "gretl_LU_solve: dgetrs gave info = %d\n",
		    (int) info);
	    err = E_DATA;
	}
    }

    free(ipiv);

    return err;
}
