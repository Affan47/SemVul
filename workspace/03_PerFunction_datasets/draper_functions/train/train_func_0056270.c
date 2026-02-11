get_tile_info(int tile_index)
{
	int code = videoram[tile_index*2];
	int attr = videoram[tile_index*2+1];
	int tile_number = code + ((attr & 0xc0) << 2) + 0x400 + 0x800 * char_bank;
	int flags = ((attr & 0x08) ? TILE_FLIPX : 0) | ((attr & 0x10) ? TILE_FLIPY : 0);

	SET_TILE_INFO(
			0,
			tile_number,
			attr & 0x0f,
			flags)
}
