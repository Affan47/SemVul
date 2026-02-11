gretl_matrix_get_row (const gretl_matrix *m, int i, gretl_vector *v)
{
    int j, nc = gretl_matrix_cols(m);

    if (gretl_vector_get_length(v) != nc) {
	return E_NONCONF;
    }

    for (j=0; j<nc; j++) {
	gretl_vector_set(v, j, gretl_matrix_get(m, i, j));
    }

    return 0;
}
