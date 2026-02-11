get_bg_tile_info(int tile_index)
{
	UINT8 *tilerom = memory_region(REGION_GFX5);

	int attr = tilerom[tile_index];
	int code = attr & 0x3f;
	int color = tilerom[tile_index + (8 * 8)];
	int flags = ((attr & 0x40) ? TILE_FLIPX : 0) | ((attr & 0x80) ? TILE_FLIPY : 0);

	SET_TILE_INFO(1, code, color, flags)
}
