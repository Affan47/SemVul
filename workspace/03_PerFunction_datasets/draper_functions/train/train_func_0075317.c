isl_union_map_add_map(__isl_take isl_union_map *umap,
	__isl_take isl_map *map)
{
	uint32_t hash;
	struct isl_hash_table_entry *entry;

	if (!map || !umap)
		goto error;

	if (isl_map_plain_is_empty(map)) {
		isl_map_free(map);
		return umap;
	}

	if (!isl_space_match(map->dim, isl_dim_param, umap->dim, isl_dim_param)) {
		umap = isl_union_map_align_params(umap, isl_map_get_space(map));
		map = isl_map_align_params(map, isl_union_map_get_space(umap));
	}

	umap = isl_union_map_cow(umap);

	if (!map || !umap)
		goto error;

	hash = isl_space_get_hash(map->dim);
	entry = isl_hash_table_find(umap->dim->ctx, &umap->table, hash,
				    &has_dim, map->dim, 1);
	if (!entry)
		goto error;

	if (!entry->data)
		entry->data = map;
	else {
		entry->data = isl_map_union(entry->data, isl_map_copy(map));
		if (!entry->data)
			goto error;
		isl_map_free(map);
	}

	return umap;
error:
	isl_map_free(map);
	isl_union_map_free(umap);
	return NULL;
}
