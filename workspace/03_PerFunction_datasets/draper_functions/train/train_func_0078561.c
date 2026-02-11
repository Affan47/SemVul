union_map_forall_user(__isl_keep isl_union_map *umap,
	int (*fn)(__isl_keep isl_map *map, void *user), void *user)
{
	struct isl_forall_user_data data = { 1, fn, user };

	if (!umap)
		return -1;

	if (isl_hash_table_foreach(umap->dim->ctx, &umap->table,
				   &forall_user_entry, &data) < 0 && data.res)
		return -1;

	return data.res;
}
