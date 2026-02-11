gel_matrixw_get_vregion (GelMatrixW *m, int *reg, int len)
{
	GelMatrix *vec;
	int i;

	g_return_val_if_fail (m != NULL, NULL);
	g_return_val_if_fail (reg != NULL, NULL);
	g_return_val_if_fail (len >= 1, NULL);

#ifdef MATRIX_DEBUG
	printf ("%s\n", G_GNUC_PRETTY_FUNCTION);
#endif

	vec = gel_matrix_new ();
	gel_matrix_set_size (vec, len, 1, FALSE );

	for (i = 0; i < len; i++) {
		GelETree *t = gel_matrixw_get_vindex (m, reg[i]);
		if (t != NULL)
			t = gel_copynode (t);
		gel_matrix_index (vec, i, 0) = t;
	}

	return gel_matrixw_new_with_matrix (vec);
}
