metro_K053936_get_tile_info(int tile_index)
{
	int code = metro_K053936_ram[tile_index];

	SET_TILE_INFO(
			2,
			code & 0x7fff,
			0x1e,
			0)
}
