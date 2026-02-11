gretl_matrix_hdproduct_new (const gretl_matrix *A,
			    const gretl_matrix *B,
			    int *err)
{
    gretl_matrix *K;
    int p, q, r;

    if (gretl_is_null_matrix(A) || gretl_is_null_matrix(B)) {
	*err = E_DATA;
	return NULL;
    }

    p = A->rows;

    if (p != B->rows) {
	*err = E_NONCONF;
	return NULL;
    }

    q = A->cols;
    r = B->cols;

    K = gretl_zero_matrix_new(p, q * r);

    if (K == NULL) {
	*err = E_ALLOC;
    } else {
	gretl_matrix_hdproduct(A, B, K);
    }

    return K;
}
