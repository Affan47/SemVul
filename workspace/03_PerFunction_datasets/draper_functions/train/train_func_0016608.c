isl_pw_aff_matching_params(__isl_keep isl_pw_aff *pa,
	__isl_keep isl_space *space)
{
	isl_space *pa_space;
	int match;

	if (!pa || !space)
		return -1;

	pa_space = isl_pw_aff_get_space(pa);

	match = isl_space_match(space, isl_dim_param, pa_space, isl_dim_param);

	isl_space_free(pa_space);
	return match;
}
