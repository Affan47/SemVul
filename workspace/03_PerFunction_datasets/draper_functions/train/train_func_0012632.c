isl_union_map_foreach_map(__isl_keep isl_union_map *umap,
	int (*fn)(__isl_take isl_map *map, void *user), void *user)
{
	struct isl_union_map_foreach_data data = { fn, user };

	if (!umap)
		return -1;

	return isl_hash_table_foreach(umap->dim->ctx, &umap->table,
				      &call_on_copy, &data);
}
