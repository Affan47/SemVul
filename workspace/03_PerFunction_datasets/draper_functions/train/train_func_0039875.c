normalize_divs_in_context(
	struct isl_basic_map *bmap, struct isl_basic_map *context)
{
	int i;
	unsigned total_context;
	int div_eq;

	div_eq = n_pure_div_eq(bmap);
	if (div_eq == 0)
		return bmap;

	if (context->n_div > 0)
		bmap = isl_basic_map_align_divs(bmap, context);

	total_context = isl_basic_map_total_dim(context);
	bmap = isl_basic_map_extend_constraints(bmap, context->n_eq, 0);
	for (i = 0; i < context->n_eq; ++i) {
		int k;
		k = isl_basic_map_alloc_equality(bmap);
		if (k < 0)
			return isl_basic_map_free(bmap);
		isl_seq_cpy(bmap->eq[k], context->eq[i], 1 + total_context);
		isl_seq_clr(bmap->eq[k] + 1 + total_context,
				isl_basic_map_total_dim(bmap) - total_context);
	}
	bmap = isl_basic_map_gauss(bmap, NULL);
	bmap = normalize_divs(bmap, NULL);
	bmap = isl_basic_map_gauss(bmap, NULL);
	return bmap;
}
