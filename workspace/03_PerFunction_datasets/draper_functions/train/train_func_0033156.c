isl_union_map_power(__isl_take isl_union_map *umap,
	int *exact)
{
	int n;
	isl_union_map *inc;
	isl_union_map *dm;

	if (!umap)
		return NULL;
	n = isl_union_map_n_map(umap);
	if (n == 0)
		return umap;
	if (n == 1) {
		struct isl_union_power up = { NULL, exact };
		isl_union_map_foreach_map(umap, &power, &up);
		isl_union_map_free(umap);
		return up.pow;
	}
	inc = increment(isl_union_map_get_space(umap));
	umap = isl_union_map_product(inc, umap);
	umap = isl_union_map_transitive_closure(umap, exact);
	umap = isl_union_map_zip(umap);
	dm = deltas_map(isl_union_map_get_space(umap));
	umap = isl_union_map_apply_domain(umap, dm);

	return umap;
}
