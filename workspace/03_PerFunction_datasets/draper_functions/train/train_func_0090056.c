isl_union_map_align_params(
	__isl_take isl_union_map *umap, __isl_take isl_space *model)
{
	struct isl_union_align data = { NULL, NULL };

	if (!umap || !model)
		goto error;

	if (isl_space_match(umap->dim, isl_dim_param, model, isl_dim_param)) {
		isl_space_free(model);
		return umap;
	}

	model = isl_space_params(model);
	data.exp = isl_parameter_alignment_reordering(umap->dim, model);
	if (!data.exp)
		goto error;

	data.res = isl_union_map_alloc(isl_space_copy(data.exp->dim),
					umap->table.n);
	if (isl_hash_table_foreach(umap->dim->ctx, &umap->table,
					&align_entry, &data) < 0)
		goto error;

	isl_reordering_free(data.exp);
	isl_union_map_free(umap);
	isl_space_free(model);
	return data.res;
error:
	isl_reordering_free(data.exp);
	isl_union_map_free(umap);
	isl_union_map_free(data.res);
	isl_space_free(model);
	return NULL;
}
