isl_basic_map_compute_divs(struct isl_basic_map *bmap)
{
	int known;
	struct isl_map *map;

	known = isl_basic_map_divs_known(bmap);
	if (known < 0)
		goto error;
	if (known)
		return isl_map_from_basic_map(bmap);

	bmap = isl_basic_map_drop_redundant_divs(bmap);

	known = isl_basic_map_divs_known(bmap);
	if (known < 0)
		goto error;
	if (known)
		return isl_map_from_basic_map(bmap);

	map = compute_divs(bmap);
	return map;
error:
	isl_basic_map_free(bmap);
	return NULL;
}
