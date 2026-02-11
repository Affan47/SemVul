isl_set_lift(__isl_take isl_set *set)
{
	int i;
	isl_space *dim;
	unsigned n_div;

	set = isl_set_align_divs(set);

	if (!set)
		return NULL;

	set = isl_set_cow(set);
	if (!set)
		return NULL;

	n_div = set->p[0]->n_div;
	dim = isl_set_get_space(set);
	dim = isl_space_lift(dim, n_div);
	if (!dim)
		goto error;
	isl_space_free(set->dim);
	set->dim = dim;

	for (i = 0; i < set->n; ++i) {
		set->p[i] = isl_basic_set_lift(set->p[i]);
		if (!set->p[i])
			goto error;
	}

	return set;
error:
	isl_set_free(set);
	return NULL;
}
