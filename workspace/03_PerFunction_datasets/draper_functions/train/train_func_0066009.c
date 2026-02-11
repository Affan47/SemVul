isl_map_flatten_domain(__isl_take isl_map *map)
{
	int i;

	if (!map)
		return NULL;

	if (!map->dim->nested[0])
		return map;

	map = isl_map_cow(map);
	if (!map)
		return NULL;

	for (i = 0; i < map->n; ++i) {
		map->p[i] = isl_basic_map_flatten_domain(map->p[i]);
		if (!map->p[i])
			goto error;
	}
	map->dim = isl_space_flatten_domain(map->dim);
	if (!map->dim)
		goto error;

	return map;
error:
	isl_map_free(map);
	return NULL;
}
