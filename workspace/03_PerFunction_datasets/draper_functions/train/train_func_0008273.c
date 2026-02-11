roadf_get_bg_tile_info(int tile_index)
{
	int code = videoram[tile_index] + ((colorram[tile_index] & 0x80) << 1) + ((colorram[tile_index] & 0x60) << 4);
	int color = colorram[tile_index] & 0x0f;
	int flags = (colorram[tile_index] & 0x10) ? TILE_FLIPX : 0;

	SET_TILE_INFO(0, code, color, flags)
}
