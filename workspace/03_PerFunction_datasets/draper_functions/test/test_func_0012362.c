get_bg_tile_info(int tile_index)
{
	int attr = prehisle_bg_videoram16[tile_index];
	int code = attr & 0x7ff;
	int color = attr >> 12;
	int flags = (attr & 0x800) ? TILE_FLIPY : 0;

	SET_TILE_INFO(2, code, color, flags)
}
