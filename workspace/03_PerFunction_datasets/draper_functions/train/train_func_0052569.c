_ba_node_xlate_from_1d(int offset_1d, int *full_offset,
				   ba_geo_system_t *my_system_geo)
{
	int i, map_offset;

	xassert(full_offset);
	map_offset = offset_1d;
	for (i = 0; i < my_system_geo->dim_count; i++) {
		full_offset[i] = map_offset % my_system_geo->dim_size[i];
		map_offset /= my_system_geo->dim_size[i];
	}
}
