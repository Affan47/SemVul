imhof_get_eigenvals (const gretl_matrix *m,
				double **plam, int *pk)
{
    gretl_matrix *E, *A;
    int err = 0;

    A = gretl_matrix_copy(m);
    if (A == NULL) {
	return E_ALLOC;
    }

    E = gretl_general_matrix_eigenvals(A, 0, &err);

    if (!err) {
	*pk = E->rows;
	*plam = gretl_matrix_steal_data(E);
    }

    gretl_matrix_free(A);
    gretl_matrix_free(E);

    return err;
}
