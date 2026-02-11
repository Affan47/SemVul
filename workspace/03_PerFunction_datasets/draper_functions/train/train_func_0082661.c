isl_ast_build_map_to_iterator(
	__isl_keep isl_ast_build *build, __isl_take isl_set *set)
{
	isl_map *map;

	map = isl_map_from_domain(set);
	map = isl_map_add_dims(map, isl_dim_out, 1);

	if (!build)
		return isl_map_free(map);

	map = isl_map_equate(map, isl_dim_in, build->depth, isl_dim_out, 0);
	map = isl_map_eliminate(map, isl_dim_in, build->depth, 1);

	return map;
}
