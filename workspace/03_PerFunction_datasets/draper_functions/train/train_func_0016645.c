isl_map_from_pw_multi_aff(__isl_take isl_pw_multi_aff *pma)
{
	int i;
	isl_map *map;

	if (!pma)
		return NULL;

	map = isl_map_empty(isl_pw_multi_aff_get_space(pma));

	for (i = 0; i < pma->n; ++i) {
		isl_multi_aff *maff;
		isl_basic_map *bmap;
		isl_map *map_i;

		maff = isl_multi_aff_copy(pma->p[i].maff);
		bmap = isl_basic_map_from_multi_aff(maff);
		map_i = isl_map_from_basic_map(bmap);
		map_i = isl_map_intersect_domain(map_i,
						isl_set_copy(pma->p[i].set));
		map = isl_map_union_disjoint(map, map_i);
	}

	isl_pw_multi_aff_free(pma);
	return map;
}
