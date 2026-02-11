coalesce_subset(__isl_keep isl_map *map, int i, int j,
	struct isl_tab **tabs, __isl_keep isl_mat *div, int *exp)
{
	isl_basic_map *bmap;
	int changed = 0;
	int *eq_i = NULL;
	int *ineq_i = NULL;

	bmap = isl_basic_map_copy(map->p[i]);
	bmap = isl_basic_set_expand_divs(bmap, isl_mat_copy(div), exp);

	if (!bmap)
		goto error;

	eq_i = eq_status_in(bmap, tabs[j]);
	if (bmap->n_eq && !eq_i)
		goto error;
	if (any(eq_i, 2 * bmap->n_eq, STATUS_ERROR))
		goto error;
	if (any(eq_i, 2 * bmap->n_eq, STATUS_SEPARATE))
		goto done;

	ineq_i = ineq_status_in(bmap, NULL, tabs[j]);
	if (bmap->n_ineq && !ineq_i)
		goto error;
	if (any(ineq_i, bmap->n_ineq, STATUS_ERROR))
		goto error;
	if (any(ineq_i, bmap->n_ineq, STATUS_SEPARATE))
		goto done;

	if (all(eq_i, 2 * map->p[i]->n_eq, STATUS_VALID) &&
	    all(ineq_i, map->p[i]->n_ineq, STATUS_VALID)) {
		drop(map, j, tabs);
		changed = 1;
	}

done:
	isl_basic_map_free(bmap);
	free(eq_i);
	free(ineq_i);
	return 0;
error:
	isl_basic_map_free(bmap);
	free(eq_i);
	free(ineq_i);
	return -1;
}
