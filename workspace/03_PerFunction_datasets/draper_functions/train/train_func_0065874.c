isl_term_free(__isl_take isl_term *term)
{
	if (!term)
		return;

	if (--term->ref > 0)
		return;

	isl_space_free(term->dim);
	isl_mat_free(term->div);
	isl_int_clear(term->n);
	isl_int_clear(term->d);
	free(term);
}
