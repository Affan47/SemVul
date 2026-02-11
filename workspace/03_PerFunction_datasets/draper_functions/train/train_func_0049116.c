isl_map_is_disjoint(__isl_keep isl_map *map1, __isl_keep isl_map *map2)
{
	int disjoint;
	int intersect;
	isl_map *test;

	disjoint = isl_map_plain_is_disjoint(map1, map2);
	if (disjoint < 0 || disjoint)
		return disjoint;

	disjoint = isl_map_is_empty(map1);
	if (disjoint < 0 || disjoint)
		return disjoint;

	disjoint = isl_map_is_empty(map2);
	if (disjoint < 0 || disjoint)
		return disjoint;

	intersect = isl_map_plain_is_universe(map1);
	if (intersect < 0 || intersect)
		return intersect < 0 ? -1 : 0;

	intersect = isl_map_plain_is_universe(map2);
	if (intersect < 0 || intersect)
		return intersect < 0 ? -1 : 0;

	test = isl_map_intersect(isl_map_copy(map1), isl_map_copy(map2));
	disjoint = isl_map_is_empty(test);
	isl_map_free(test);

	return disjoint;
}
