get_alpha_tile_info(int tile_index)
{
	UINT16 data = atarigen_alpha[tile_index];
	int code = data & 0x3ff;
	int color = ((data >> 10) & 0x0f) | ((data >> 9) & 0x20);
	int opaque = data & 0x8000;
	SET_TILE_INFO(1, code, color, opaque ? TILE_IGNORE_TRANSPARENCY : 0);
}
