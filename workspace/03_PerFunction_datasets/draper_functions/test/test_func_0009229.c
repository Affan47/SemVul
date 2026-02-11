gretl_matrix_multiply_new (const gretl_matrix *a,
					 const gretl_matrix *b,
					 int *err)
{
    gretl_matrix *c;

    if (gretl_is_null_matrix(a) || gretl_is_null_matrix(b)) {
	*err = E_DATA;
	return NULL;
    }

    if (a->cols != b->rows) {
	fprintf(stderr, "gretl_matrix_multiply_new: requested (%d x %d) * (%d x %d)\n",
		a->rows, a->cols, b->rows, b->cols);
	*err = E_NONCONF;
	return NULL;
    }

    c = gretl_matrix_alloc(a->rows, b->cols);
    if (c == NULL) {
	*err = E_ALLOC;
	return NULL;
    }

    *err = gretl_matrix_multiply_mod(a, GRETL_MOD_NONE,
				     b, GRETL_MOD_NONE,
				     c, GRETL_MOD_NONE);

    if (*err) {
	gretl_matrix_free(c);
	c = NULL;
    }

    return c;
}
