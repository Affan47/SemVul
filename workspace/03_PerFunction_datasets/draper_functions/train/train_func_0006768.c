set_iterator_names(
	__isl_keep isl_ast_build *build, __isl_take isl_pw_multi_aff *pma)
{
	int i, n;

	n = isl_pw_multi_aff_dim(pma, isl_dim_in);
	for (i = 0; i < n; ++i) {
		isl_id *id;

		id = isl_ast_build_get_iterator_id(build, i);
		pma = isl_pw_multi_aff_set_dim_id(pma, isl_dim_in, i, id);
	}

	return pma;
}
