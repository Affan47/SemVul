isl_basic_map_sort_constraints(
	struct isl_basic_map *bmap)
{
	unsigned total;

	if (!bmap)
		return NULL;
	if (bmap->n_ineq == 0)
		return bmap;
	if (ISL_F_ISSET(bmap, ISL_BASIC_MAP_NORMALIZED))
		return bmap;
	total = isl_basic_map_total_dim(bmap);
	if (isl_sort(bmap->ineq, bmap->n_ineq, sizeof(isl_int *),
		    &sort_constraint_cmp, &total) < 0)
		return isl_basic_map_free(bmap);
	return bmap;
}
