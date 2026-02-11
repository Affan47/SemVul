isl_map_free(struct isl_map *map)
{
	int i;

	if (!map)
		return NULL;

	if (--map->ref > 0)
		return NULL;

	isl_ctx_deref(map->ctx);
	for (i = 0; i < map->n; ++i)
		isl_basic_map_free(map->p[i]);
	isl_space_free(map->dim);
	free(map);

	return NULL;
}
