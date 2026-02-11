basic_map_diff_is_empty(__isl_keep isl_basic_map *bmap,
	__isl_keep isl_map *map)
{
	int r;
	struct isl_is_empty_diff_collector edc;

	r = isl_basic_map_plain_is_empty(bmap);
	if (r)
		return r;

	edc.dc.add = &basic_map_is_empty_add;
	edc.empty = 1;
	r = basic_map_collect_diff(isl_basic_map_copy(bmap),
				   isl_map_copy(map), &edc.dc);
	if (!edc.empty)
		return 0;

	return r < 0 ? -1 : 1;
}
