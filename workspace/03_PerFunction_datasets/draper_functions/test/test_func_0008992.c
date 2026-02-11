isl_map_coalesce(struct isl_map *map)
{
	int i;
	unsigned n;
	struct isl_tab **tabs = NULL;

	map = isl_map_remove_empty_parts(map);
	if (!map)
		return NULL;

	if (map->n <= 1)
		return map;

	map = isl_map_sort_divs(map);
	map = isl_map_cow(map);

	tabs = isl_calloc_array(map->ctx, struct isl_tab *, map->n);
	if (!tabs)
		goto error;

	n = map->n;
	for (i = 0; i < map->n; ++i) {
		tabs[i] = isl_tab_from_basic_map(map->p[i], 0);
		if (!tabs[i])
			goto error;
		if (!ISL_F_ISSET(map->p[i], ISL_BASIC_MAP_NO_IMPLICIT))
			if (isl_tab_detect_implicit_equalities(tabs[i]) < 0)
				goto error;
		map->p[i] = isl_tab_make_equalities_explicit(tabs[i],
								map->p[i]);
		if (!map->p[i])
			goto error;
		if (!ISL_F_ISSET(map->p[i], ISL_BASIC_MAP_NO_REDUNDANT))
			if (isl_tab_detect_redundant(tabs[i]) < 0)
				goto error;
	}
	for (i = map->n - 1; i >= 0; --i)
		if (tabs[i]->empty)
			drop(map, i, tabs);

	map = coalesce(map, tabs);

	if (map)
		for (i = 0; i < map->n; ++i) {
			map->p[i] = isl_basic_map_update_from_tab(map->p[i],
								    tabs[i]);
			map->p[i] = isl_basic_map_gauss(map->p[i], NULL);
			map->p[i] = isl_basic_map_finalize(map->p[i]);
			if (!map->p[i])
				goto error;
			ISL_F_SET(map->p[i], ISL_BASIC_MAP_NO_IMPLICIT);
			ISL_F_SET(map->p[i], ISL_BASIC_MAP_NO_REDUNDANT);
		}

	for (i = 0; i < n; ++i)
		isl_tab_free(tabs[i]);

	free(tabs);

	return map;
error:
	if (tabs)
		for (i = 0; i < n; ++i)
			isl_tab_free(tabs[i]);
	free(tabs);
	isl_map_free(map);
	return NULL;
}
