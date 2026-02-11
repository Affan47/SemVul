get_bg_tile_info(int tile_index)
{
	int code = safarir_ram[tile_index + 0x400];

	SET_TILE_INFO(0, code & 0x7f, code >> 7, 0)
}
