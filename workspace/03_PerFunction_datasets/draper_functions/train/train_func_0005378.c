coalesce_or_drop_more_redundant_divs(
	struct isl_basic_map *bmap, int *pairs, int n)
{
	int i, l, u;
	unsigned dim;

	dim = isl_space_dim(bmap->dim, isl_dim_all);

	for (i = 0; i < bmap->n_div; ++i) {
		if (!pairs[i])
			continue;
		for (l = 0; l < bmap->n_ineq; ++l) {
			if (!isl_int_is_one(bmap->ineq[l][1 + dim + i]))
				continue;
			for (u = 0; u < bmap->n_ineq; ++u) {
				int c;

				if (!isl_int_is_negone(bmap->ineq[u][1+dim+i]))
					continue;
				c = div_find_coalesce(bmap, pairs, i, l, u);
				if (c < 0)
					continue;
				free(pairs);
				bmap = coalesce_divs(bmap, i, c, l, u);
				return isl_basic_map_drop_redundant_divs(bmap);
			}
		}
	}

	if (ISL_F_ISSET(bmap, ISL_BASIC_MAP_EMPTY))
		return bmap;

	return drop_more_redundant_divs(bmap, pairs, n);
}
