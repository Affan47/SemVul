fg_get_tile_info(int tile_index)
{
	int tile = tecmo16_videoram[tile_index] & 0x1fff;
	int color = tecmo16_colorram[tile_index] & 0x0f;

	SET_TILE_INFO(
			1,
			tile,
			color,
			0)
}
