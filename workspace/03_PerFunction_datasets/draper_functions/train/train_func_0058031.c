isl_multi_aff_substitute_equalities(
	__isl_take isl_multi_aff *maff, __isl_take isl_basic_set *eq)
{
	int i;

	maff = isl_multi_aff_cow(maff);
	if (!maff || !eq)
		goto error;

	for (i = 0; i < maff->n; ++i) {
		maff->p[i] = isl_aff_substitute_equalities(maff->p[i],
						    isl_basic_set_copy(eq));
		if (!maff->p[i])
			goto error;
	}

	isl_basic_set_free(eq);
	return maff;
error:
	isl_basic_set_free(eq);
	isl_multi_aff_free(maff);
	return NULL;
}
