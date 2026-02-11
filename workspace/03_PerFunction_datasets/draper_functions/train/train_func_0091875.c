pw_aff_zero_set(__isl_take isl_pw_aff *pwaff,
	int complement)
{
	int i;
	isl_set *set;

	if (!pwaff)
		return NULL;

	set = isl_set_empty(isl_pw_aff_get_domain_space(pwaff));

	for (i = 0; i < pwaff->n; ++i) {
		isl_basic_set *bset;
		isl_set *set_i, *zero;
		int rational;

		rational = isl_set_has_rational(pwaff->p[i].set);
		bset = aff_zero_basic_set(isl_aff_copy(pwaff->p[i].aff),
						rational);
		zero = isl_set_from_basic_set(bset);
		set_i = isl_set_copy(pwaff->p[i].set);
		if (complement)
			set_i = isl_set_subtract(set_i, zero);
		else
			set_i = isl_set_intersect(set_i, zero);
		set = isl_set_union_disjoint(set, set_i);
	}

	isl_pw_aff_free(pwaff);

	return set;
}
