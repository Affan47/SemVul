QR_solve (gretl_matrix *a, gretl_matrix *b,
		     integer m, integer n, integer nrhs,
		     integer ldb)
{
    char trans = 'N';
    integer info;
    integer lda = m;
    integer lwork = -1;
    double *work;
    int err = 0;

    if (m > n && is_block_matrix(b)) {
	matrix_block_error("QR solve");
	return E_DATA;
    }

    work = lapack_malloc(sizeof *work);
    if (work == NULL) {
	return E_ALLOC;
    }

    dgels_(&trans, &m, &n, &nrhs, a->val, &lda, b->val, &ldb,
	   work, &lwork, &info);
    if (info != 0) {
	return wspace_fail(info, work[0]);
    }

    lwork = (integer) work[0];

    work = lapack_realloc(work, lwork * sizeof *work);
    if (work == NULL) {
	return E_ALLOC;
    }

    dgels_(&trans, &m, &n, &nrhs, a->val, &lda, b->val, &ldb,
	   work, &lwork, &info);
    if (info != 0) {
	fprintf(stderr, "QR_solve: dgels gave info = %d\n",
		(int) info);
	err = E_DATA;
    }


    if (!err && m > n) {
	gretl_matrix *c;

	c = gretl_matrix_trim_rows(b, 0, m - n, &err);
	if (!err) {
	    matrix_grab_content(b, c);
	    gretl_matrix_free(c);
	}
    }

    lapack_free(work);

    return err;
}
