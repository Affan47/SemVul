gel_matrixw_new(void)
{
	GelMatrixW *m;
	NEW_MATRIX (m);

#ifdef MATRIX_DEBUG
	printf ("%s\n", G_GNUC_PRETTY_FUNCTION);
#endif

	m->m = gel_matrix_new();
	m->m->use = 1;


	m->cached_value_only = 0;
	m->cached_value_only_real = 0;
	m->cached_value_only_rational = 0;
	m->cached_value_only_integer = 0;
	m->cached_value_or_bool_only = 0;
	m->rref = 0;

	m->tr = 0;
	m->regx = NULL;
	m->regy = NULL;
	m->regw = m->m->width;
	m->regh = m->m->height;

	return m;
}
