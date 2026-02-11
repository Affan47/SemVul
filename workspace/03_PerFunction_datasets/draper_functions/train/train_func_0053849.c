isl_basic_map_sort_divs(
	__isl_take isl_basic_map *bmap)
{
	int i, j;
	unsigned total;

	bmap = isl_basic_map_order_divs(bmap);
	if (!bmap)
		return NULL;
	if (bmap->n_div <= 1)
		return bmap;

	total = 2 + isl_basic_map_total_dim(bmap);
	for (i = 1; i < bmap->n_div; ++i) {
		for (j = i - 1; j >= 0; --j) {
			if (bmap_cmp_row(bmap, j, j + 1, total) <= 0)
				break;
			isl_basic_map_swap_div(bmap, j, j + 1);
		}
	}

	return bmap;
}
