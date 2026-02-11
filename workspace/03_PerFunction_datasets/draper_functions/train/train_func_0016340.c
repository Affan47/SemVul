n_non_redundant(isl_ctx *ctx, struct isl_tab *tab,
	int offset, int **index)
{
	int i, n;
	int n_test = tab->n_con - offset;

	if (isl_tab_detect_redundant(tab) < 0)
		return -1;

	if (n_test == 0)
		return 0;
	if (!*index)
		*index = isl_alloc_array(ctx, int, n_test);
	if (!*index)
		return -1;

	for (n = 0, i = 0; i < n_test; ++i) {
		int r;
		r = isl_tab_is_redundant(tab, offset + i);
		if (r < 0)
			return -1;
		if (r)
			continue;
		(*index)[n++] = i;
	}

	return n;
}
