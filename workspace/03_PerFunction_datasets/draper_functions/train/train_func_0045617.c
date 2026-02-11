isl_basic_map_neg(struct isl_basic_map *bmap)
{
	int i, j;
	unsigned off, n;

	bmap = isl_basic_map_cow(bmap);
	if (!bmap)
		return NULL;

	n = isl_basic_map_dim(bmap, isl_dim_out);
	off = isl_basic_map_offset(bmap, isl_dim_out);
	for (i = 0; i < bmap->n_eq; ++i)
		for (j = 0; j < n; ++j)
			isl_int_neg(bmap->eq[i][off+j], bmap->eq[i][off+j]);
	for (i = 0; i < bmap->n_ineq; ++i)
		for (j = 0; j < n; ++j)
			isl_int_neg(bmap->ineq[i][off+j], bmap->ineq[i][off+j]);
	for (i = 0; i < bmap->n_div; ++i)
		for (j = 0; j < n; ++j)
			isl_int_neg(bmap->div[i][1+off+j], bmap->div[i][1+off+j]);
	bmap = isl_basic_map_gauss(bmap, NULL);
	return isl_basic_map_finalize(bmap);
}
