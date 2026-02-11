contains(struct isl_map *map, int i, int *ineq_i,
	struct isl_tab *tab)
{
	int k, l;
	unsigned dim;

	dim = isl_basic_map_total_dim(map->p[i]);
	for (k = 0; k < map->p[i]->n_eq; ++k) {
		for (l = 0; l < 2; ++l) {
			int stat;
			isl_seq_neg(map->p[i]->eq[k], map->p[i]->eq[k], 1+dim);
			stat = status_in(map->p[i]->eq[k], tab);
			if (stat != STATUS_VALID)
				return 0;
		}
	}

	for (k = 0; k < map->p[i]->n_ineq; ++k) {
		int stat;
		if (ineq_i[k] == STATUS_REDUNDANT)
			continue;
		stat = status_in(map->p[i]->ineq[k], tab);
		if (stat != STATUS_VALID)
			return 0;
	}
	return 1;
}
