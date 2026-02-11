Matrix(GB_PAINT *d, int set, GB_TRANSFORM matrix)
{
	cairo_matrix_t *t = (cairo_matrix_t *)matrix;

	if (set)
	{
		if (t)
			cairo_set_matrix(CONTEXT(d), t);
		else
		{
			if (EXTRA(d)->print_context)
				cairo_set_matrix(CONTEXT(d), &EXTRA(d)->init);
			else
				cairo_identity_matrix(CONTEXT(d));
		}
	}
	else
		cairo_get_matrix(CONTEXT(d), t);
}
