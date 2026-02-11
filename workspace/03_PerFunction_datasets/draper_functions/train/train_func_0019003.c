soup_path_map_free (SoupPathMap *map)
{
	SoupPathMapping *mappings = (SoupPathMapping *)map->mappings->data;
	int i;

	for (i = 0; i < map->mappings->len; i++) {
		g_free (mappings[i].path);
		if (map->free_func)
			map->free_func (mappings[i].data);
	}
	g_array_free (map->mappings, TRUE);

	g_slice_free (SoupPathMap, map);
}
