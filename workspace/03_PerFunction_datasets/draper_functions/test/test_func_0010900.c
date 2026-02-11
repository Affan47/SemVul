razmataz_get_fg_tile_info(int tile_index)
{
	int code = videoram[tile_index];
	int color = (color_codes[code] & 0x0f) + 16 * (*zaxxon_char_color_bank & 0x01);

	SET_TILE_INFO(0, code, color, 0)
}
