clear_coalesce_info(int n, struct isl_coalesce_info *info)
{
	int i;

	if (!info)
		return;

	for (i = 0; i < n; ++i) {
		isl_basic_map_free(info[i].bmap);
		isl_tab_free(info[i].tab);
	}

	free(info);
}
