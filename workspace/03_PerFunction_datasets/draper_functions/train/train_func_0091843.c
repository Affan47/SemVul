get_fg_tile_info(int tile_index)
{
	data8_t code = brkthru_videoram[tile_index];
	SET_TILE_INFO(0, code, 0, 0)
}
