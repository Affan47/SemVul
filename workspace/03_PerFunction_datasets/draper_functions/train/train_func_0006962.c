isl_ast_build_clear_local_info(
	__isl_take isl_ast_build *build)
{
	isl_space *space;

	build = isl_ast_build_cow(build);
	if (!build)
		return NULL;

	space = isl_union_map_get_space(build->options);
	isl_union_map_free(build->options);
	build->options = isl_union_map_empty(space);

	build->at_each_domain = NULL;
	build->at_each_domain_user = NULL;
	build->before_each_for = NULL;
	build->before_each_for_user = NULL;
	build->after_each_for = NULL;
	build->after_each_for_user = NULL;
	build->before_each_mark = NULL;
	build->before_each_mark_user = NULL;
	build->after_each_mark = NULL;
	build->after_each_mark_user = NULL;
	build->create_leaf = NULL;
	build->create_leaf_user = NULL;

	if (!build->options)
		return isl_ast_build_free(build);

	return build;
}
