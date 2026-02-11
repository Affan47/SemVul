isl_multi_union_pw_aff_from_multi_pw_aff(
	__isl_take isl_multi_pw_aff *mpa)
{
	int i, n;
	isl_space *space;
	isl_multi_union_pw_aff *mupa;

	if (!mpa)
		return NULL;

	space = isl_multi_pw_aff_get_space(mpa);
	space = isl_space_range(space);
	mupa = isl_multi_union_pw_aff_alloc(space);

	n = isl_multi_pw_aff_dim(mpa, isl_dim_out);
	for (i = 0; i < n; ++i) {
		isl_pw_aff *pa;
		isl_union_pw_aff *upa;

		pa = isl_multi_pw_aff_get_pw_aff(mpa, i);
		upa = isl_union_pw_aff_from_pw_aff(pa);
		mupa = isl_multi_union_pw_aff_set_union_pw_aff(mupa, i, upa);
	}

	isl_multi_pw_aff_free(mpa);

	return mupa;
}
