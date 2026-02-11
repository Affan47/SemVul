coalesce_pair(__isl_keep isl_map *map, int i, int j,
	struct isl_tab **tabs)
{
	int same;

	same = same_divs(map->p[i], map->p[j]);
	if (same < 0)
		return -1;
	if (same)
		return coalesce_local_pair(map, i, j, tabs);

	return check_coalesce_subset(map, i, j, tabs);
}
