o2hb_fill_node_map_from_callback(unsigned long *map,
					     unsigned bytes)
{
	BUG_ON(bytes < (BITS_TO_LONGS(O2NM_MAX_NODES) * sizeof(unsigned long)));

	memcpy(map, &o2hb_live_node_bitmap, bytes);
}
