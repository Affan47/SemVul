isl_local_space_get_active(__isl_keep isl_local_space *ls, isl_int *l)
{
	int i, j;
	isl_ctx *ctx;
	int *active = NULL;
	unsigned total;
	unsigned offset;

	ctx = isl_local_space_get_ctx(ls);
	total = isl_local_space_dim(ls, isl_dim_all);
	active = isl_calloc_array(ctx, int, total);
	if (total && !active)
		return NULL;

	for (i = 0; i < total; ++i)
		active[i] = !isl_int_is_zero(l[i]);

	offset = isl_local_space_offset(ls, isl_dim_div) - 1;
	for (i = ls->div->n_row - 1; i >= 0; --i) {
		if (!active[offset + i])
			continue;
		for (j = 0; j < total; ++j)
			active[j] |= !isl_int_is_zero(ls->div->row[i][2 + j]);
	}

	return active;
}
