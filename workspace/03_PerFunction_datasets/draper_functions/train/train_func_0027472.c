same_divs(__isl_keep isl_basic_map *bmap1,
	__isl_keep isl_basic_map *bmap2)
{
	int i;
	int known;
	int total;

	if (!bmap1 || !bmap2)
		return -1;
	if (bmap1->n_div != bmap2->n_div)
		return 0;

	if (bmap1->n_div == 0)
		return 1;

	known = isl_basic_map_divs_known(bmap1);
	if (known < 0 || !known)
		return known;
	known = isl_basic_map_divs_known(bmap2);
	if (known < 0 || !known)
		return known;

	total = isl_basic_map_total_dim(bmap1);
	for (i = 0; i < bmap1->n_div; ++i)
		if (!isl_seq_eq(bmap1->div[i], bmap2->div[i], 2 + total))
			return 0;

	return 1;
}
