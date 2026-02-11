isl_basic_map_gauss(
	struct isl_basic_map *bmap, int *progress)
{
	int k;
	int done;
	int last_var;
	unsigned total_var;
	unsigned total;

	bmap = isl_basic_map_order_divs(bmap);

	if (!bmap)
		return NULL;

	total = isl_basic_map_total_dim(bmap);
	total_var = total - bmap->n_div;

	last_var = total - 1;
	for (done = 0; done < bmap->n_eq; ++done) {
		for (; last_var >= 0; --last_var) {
			for (k = done; k < bmap->n_eq; ++k)
				if (!isl_int_is_zero(bmap->eq[k][1+last_var]))
					break;
			if (k < bmap->n_eq)
				break;
		}
		if (last_var < 0)
			break;
		if (k != done)
			swap_equality(bmap, k, done);
		if (isl_int_is_neg(bmap->eq[done][1+last_var]))
			isl_seq_neg(bmap->eq[done], bmap->eq[done], 1+total);

		eliminate_var_using_equality(bmap, last_var, bmap->eq[done], 1,
						progress);

		if (last_var >= total_var &&
		    isl_int_is_zero(bmap->div[last_var - total_var][0])) {
			unsigned div = last_var - total_var;
			isl_seq_neg(bmap->div[div]+1, bmap->eq[done], 1+total);
			isl_int_set_si(bmap->div[div][1+1+last_var], 0);
			isl_int_set(bmap->div[div][0],
				    bmap->eq[done][1+last_var]);
			if (progress)
				*progress = 1;
			ISL_F_CLR(bmap, ISL_BASIC_MAP_NORMALIZED);
		}
	}
	if (done == bmap->n_eq)
		return bmap;
	for (k = done; k < bmap->n_eq; ++k) {
		if (isl_int_is_zero(bmap->eq[k][0]))
			continue;
		return isl_basic_map_set_to_empty(bmap);
	}
	isl_basic_map_free_equality(bmap, bmap->n_eq-done);
	return bmap;
}
