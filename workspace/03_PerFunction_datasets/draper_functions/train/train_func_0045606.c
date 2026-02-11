get_bg_tile_info(int tile_index)
{
	int code = videoram[tile_index] + 256 * charbank;
	int color = (colorram[tile_index] & 0x38) >> 3;

	SET_TILE_INFO(1, code, color, 0)
}
