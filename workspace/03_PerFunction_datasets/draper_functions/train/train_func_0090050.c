basic_map_partial_lexopt_base_map(
	__isl_take isl_basic_map *bmap, __isl_take isl_basic_set *dom,
	__isl_give isl_set **empty, int max)
{
	isl_map *result = NULL;
	struct isl_sol *sol;
	struct isl_sol_map *sol_map;

	sol = basic_map_partial_lexopt_base(bmap, dom, empty, max,
					    &sol_map_init);
	if (!sol)
		return NULL;
	sol_map = (struct isl_sol_map *) sol;

	result = isl_map_copy(sol_map->map);
	if (empty)
		*empty = isl_set_copy(sol_map->empty);
	sol_free(&sol_map->sol);
	return result;
}
