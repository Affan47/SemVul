isl_union_map_is_single_valued(__isl_keep isl_union_map *umap)
{
	isl_union_map *test;
	int sv;

	if (isl_union_map_n_map(umap) == 1) {
		isl_map *map;
		umap = isl_union_map_copy(umap);
		map = isl_map_from_union_map(umap);
		sv = isl_map_is_single_valued(map);
		isl_map_free(map);
		return sv;
	}

	test = isl_union_map_reverse(isl_union_map_copy(umap));
	test = isl_union_map_apply_range(test, isl_union_map_copy(umap));

	sv = union_map_forall(test, &is_subset_of_identity);

	isl_union_map_free(test);

	return sv;
}
