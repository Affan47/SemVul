check_adj_eq(struct isl_map *map, int i, int j,
	struct isl_tab **tabs, int *eq_i, int *ineq_i, int *eq_j, int *ineq_j)
{
	int changed = 0;
	int k;

	if (any(eq_i, 2 * map->p[i]->n_eq, STATUS_ADJ_INEQ) &&
	    any(eq_j, 2 * map->p[j]->n_eq, STATUS_ADJ_INEQ))

		return 0;

	if (any(eq_i, 2 * map->p[i]->n_eq, STATUS_ADJ_INEQ))
		return check_adj_eq(map, j, i, tabs,
					eq_j, ineq_j, eq_i, ineq_i);


	if (any(eq_i, 2 * map->p[i]->n_eq, STATUS_CUT))
		return 0;
	if (any(ineq_i, map->p[i]->n_ineq, STATUS_CUT))

		return 0;
	if (count(ineq_i, map->p[i]->n_ineq, STATUS_ADJ_EQ) != 1 ||
	    any(ineq_j, map->p[j]->n_ineq, STATUS_ADJ_EQ) ||
	    any(ineq_i, map->p[i]->n_ineq, STATUS_ADJ_INEQ) ||
	    any(ineq_j, map->p[j]->n_ineq, STATUS_ADJ_INEQ))

		return 0;

	for (k = 0; k < map->p[i]->n_ineq; ++k)
		if (ineq_i[k] == STATUS_ADJ_EQ)
			break;

	changed = is_adj_eq_extension(map, i, j, k, tabs,
					eq_i, ineq_i, eq_j, ineq_j);
	if (changed)
		return changed;

	if (count(eq_j, 2 * map->p[j]->n_eq, STATUS_ADJ_INEQ) != 1)
		return 0;

	changed = can_wrap_in_facet(map, i, j, k, tabs, eq_i, ineq_i, eq_j, ineq_j);

	return changed;
}
