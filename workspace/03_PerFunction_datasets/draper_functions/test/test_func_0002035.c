generate_code_in_space(struct isl_generate_code_data *data,
	__isl_take isl_set *set, __isl_take isl_space *space)
{
	isl_union_map *executed;
	isl_ast_build *build;
	isl_ast_graft_list *list;
	int embed;

	executed = isl_union_map_copy(data->executed);
	executed = isl_union_map_intersect_domain(executed,
						 isl_union_set_from_set(set));

	embed = !isl_set_is_params(data->build->domain);
	if (embed && !data->internal)
		executed = internal_executed(executed, space, data->build);
	if (!embed) {
		isl_set *domain;
		domain = isl_ast_build_get_domain(data->build);
		domain = isl_set_from_basic_set(isl_set_simple_hull(domain));
		executed = isl_union_map_intersect_params(executed, domain);
	}

	build = isl_ast_build_copy(data->build);
	build = isl_ast_build_product(build, space);

	list = generate_next_level(executed, build);

	list = isl_ast_graft_list_unembed(list, embed);

	data->list = isl_ast_graft_list_concat(data->list, list);

	return 0;
}
