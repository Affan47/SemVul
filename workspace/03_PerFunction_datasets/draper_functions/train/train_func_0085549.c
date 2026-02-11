isl_ast_build_compute_gist_map_domain(
	__isl_keep isl_ast_build *build, __isl_take isl_map *map)
{
	if (!build)
		goto error;

	map = isl_map_gist_domain(map, isl_set_copy(build->domain));

	return map;
error:
	isl_map_free(map);
	return NULL;
}
