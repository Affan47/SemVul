gel_matrixw_set_at_least_size (GelMatrixW *m, int width, int height)
{
	g_return_if_fail (m != NULL);
	g_return_if_fail (width >= 0);
	g_return_if_fail (height >= 0);
#ifdef MATRIX_DEBUG
	printf ("%s\n", G_GNUC_PRETTY_FUNCTION);
#endif

	if (m->tr) {
		int tmp = width;
		width = height;
		height = tmp;
	}

	if (width > m->regw || height > m->regh) {

		gel_matrixw_make_private (m, TRUE );
		make_us_a_copy (m, MAX (width, m->regw),MAX (height, m->regh));
		ensure_at_least_size (m, width, height);
	}
}
