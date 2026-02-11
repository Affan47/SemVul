get_fg_tile_info(int tile_index)
{
	int page = tile_index >> 11;
	UINT16 attr = deniam_videoram[fg_page[page] * 0x0800 + (tile_index & 0x7ff)];
	SET_TILE_INFO(
			0,
			attr,
			(attr & 0x1fc0) >> 6,
			0)
}
