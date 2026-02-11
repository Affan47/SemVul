user_matrix_vech (const gretl_matrix *m, int *err)
{
    gretl_matrix *R = NULL;

    if (gretl_is_null_matrix(m)) {
	R = gretl_null_matrix_new();
    } else if (m->rows != m->cols) {
	*err = E_NONCONF;
    } else {
	int n = m->rows;
	int k = n * (n + 1) / 2;

	R = gretl_matrix_alloc(k, 1);
	if (R != NULL) {
	    *err = gretl_matrix_vectorize_h(R, m);
	}
    }

    if (R == NULL && !*err) {
	*err = E_ALLOC;
    }

    return R;
}
