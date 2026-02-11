get_expanded_n_div(struct isl_find_unroll_data *data,
	__isl_keep isl_aff *lower)
{
	isl_constraint *c;
	isl_set *set;
	isl_map *it_map, *expansion;
	isl_pw_multi_aff *pma;
	int n;

	c = at_offset(data->depth, lower, 0);
	set = isl_set_copy(data->domain);
	set = isl_set_add_constraint(set, c);
	expansion = isl_map_from_basic_map(isl_basic_map_copy(data->expansion));
	set = isl_set_apply(set, expansion);
	it_map = isl_ast_build_map_to_iterator(data->build, set);
	pma = isl_pw_multi_aff_from_map(it_map);
	n = 0;
	if (isl_pw_multi_aff_foreach_piece(pma, &update_n_div, &n) < 0)
		n = -1;
	isl_pw_multi_aff_free(pma);

	return n;
}
