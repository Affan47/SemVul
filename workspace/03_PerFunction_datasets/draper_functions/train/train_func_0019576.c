gretl_vector_dot_product (const gretl_vector *a, const gretl_vector *b,
				 int *err)
{
    int i, dima, dimb;
    double dp = 0.0;

    if (gretl_is_null_matrix(a) || gretl_is_null_matrix(b)) {
	return NADBL;
    }

    dima = (a->rows > 1)? a->rows : a->cols;
    dimb = (b->rows > 1)? b->rows : b->cols;

    if (!gretl_is_vector(a) || !gretl_is_vector(b) || dima != dimb) {
	if (err != NULL) {
	    *err = E_NONCONF;
	}
	dp = NADBL;
    } else {
	for (i=0; i<dima; i++) {
	    dp += a->val[i] * b->val[i];
	}
    }

    return dp;
}
