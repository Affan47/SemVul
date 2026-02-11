isl_multi_pw_aff_coalesce(
	__isl_take isl_multi_pw_aff *mpa)
{
	int i;

	if (!mpa)
		return NULL;

	for (i = 0; i < mpa->n; ++i) {
		isl_pw_aff *pa = isl_pw_aff_copy(mpa->p[i]);
		pa = isl_pw_aff_coalesce(pa);
		if (!pa)
			return isl_multi_pw_aff_free(mpa);
		isl_pw_aff_free(mpa->p[i]);
		mpa->p[i] = pa;
	}

	return mpa;
}
