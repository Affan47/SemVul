update_values(
	__isl_take isl_ast_build *build, __isl_take isl_basic_set *bounds)
{
	int sv;
	isl_pw_multi_aff *pma;
	isl_aff *aff = NULL;
	isl_map *it_map;
	isl_set *set;

	set = isl_set_from_basic_set(bounds);
	set = isl_set_intersect(set, isl_set_copy(build->domain));
	set = intersect_stride_constraint(set, build);
	it_map = isl_ast_build_map_to_iterator(build, set);

	sv = isl_map_is_single_valued(it_map);
	if (sv < 0)
		build = isl_ast_build_free(build);
	if (!build || !sv) {
		isl_map_free(it_map);
		return build;
	}

	pma = isl_pw_multi_aff_from_map(it_map);
	build->value = isl_pw_multi_aff_get_pw_aff(pma, 0);
	build->value = isl_ast_build_compute_gist_pw_aff(build, build->value);
	build->value = isl_pw_aff_coalesce(build->value);
	isl_pw_multi_aff_free(pma);

	if (!build->value)
		return isl_ast_build_free(build);

	if (isl_pw_aff_n_piece(build->value) != 1)
		return build;

	isl_pw_aff_foreach_piece(build->value, &extract_single_piece, &aff);

	build->values = isl_multi_aff_set_aff(build->values, build->depth, aff);
	if (!build->values)
		return isl_ast_build_free(build);
	isl_ast_build_reset_schedule_map(build);
	return build;
}
