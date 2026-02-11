eliminate_divs_eq(
		struct isl_basic_map *bmap, int *progress)
{
	int d;
	int i;
	int modified = 0;
	unsigned off;

	bmap = isl_basic_map_order_divs(bmap);

	if (!bmap)
		return NULL;

	off = 1 + isl_space_dim(bmap->dim, isl_dim_all);

	for (d = bmap->n_div - 1; d >= 0 ; --d) {
		for (i = 0; i < bmap->n_eq; ++i) {
			if (!isl_int_is_one(bmap->eq[i][off + d]) &&
			    !isl_int_is_negone(bmap->eq[i][off + d]))
				continue;
			if (!ok_to_eliminate_div(bmap, bmap->eq[i], d))
				continue;
			modified = 1;
			*progress = 1;
			eliminate_div(bmap, bmap->eq[i], d, 1);
			isl_basic_map_drop_equality(bmap, i);
			break;
		}
	}
	if (modified)
		return eliminate_divs_eq(bmap, progress);
	return bmap;
}
