get_bg_tile_info(int tile_index)
{
	int code = (news_bgram[tile_index*2] << 8) | news_bgram[tile_index*2+1];
	int color = (code & 0xf000) >> 12;

	code &= 0x0fff;
	if ((code & 0x0e00) == 0x0e00) code = (code & 0x1ff) | (bgpic << 9);

	SET_TILE_INFO(
			0,
			code,
			color,
			0)
}
