gretl_matrix_kronecker_product_new (const gretl_matrix *A,
				    const gretl_matrix *B,
				    int *err)
{
    gretl_matrix *K;
    int p, q, r, s;

    if (gretl_is_null_matrix(A) || gretl_is_null_matrix(B)) {
	*err = E_DATA;
	return NULL;
    }

    p = A->rows;
    q = A->cols;
    r = B->rows;
    s = B->cols;

    K = gretl_matrix_alloc(p * r, q * s);

    if (K == NULL) {
	*err = E_ALLOC;
    } else {
	gretl_matrix_kronecker_product(A, B, K);
    }

    return K;
}
