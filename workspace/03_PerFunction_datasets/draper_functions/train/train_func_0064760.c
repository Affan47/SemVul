at_most_one_non_fixed(struct isl_set_map_pair *domain,
	int *order, int n, int depth)
{
	int i;
	int non_fixed = -1;

	for (i = 0; i < n; ++i) {
		int f;

		f = isl_set_plain_is_fixed(domain[order[i]].set,
						isl_dim_set, depth, NULL);
		if (f < 0)
			return -1;
		if (f)
			continue;
		if (non_fixed >= 0)
			return 0;
		non_fixed = i;
	}

	return 1;
}
