isl_basic_map_contains(struct isl_basic_map *bmap, struct isl_vec *vec)
{
	int i;
	unsigned total;
	isl_int s;

	total = 1 + isl_basic_map_total_dim(bmap);
	if (total != vec->size)
		return -1;

	isl_int_init(s);

	for (i = 0; i < bmap->n_eq; ++i) {
		isl_seq_inner_product(vec->el, bmap->eq[i], total, &s);
		if (!isl_int_is_zero(s)) {
			isl_int_clear(s);
			return 0;
		}
	}

	for (i = 0; i < bmap->n_ineq; ++i) {
		isl_seq_inner_product(vec->el, bmap->ineq[i], total, &s);
		if (isl_int_is_neg(s)) {
			isl_int_clear(s);
			return 0;
		}
	}

	isl_int_clear(s);

	return 1;
}
