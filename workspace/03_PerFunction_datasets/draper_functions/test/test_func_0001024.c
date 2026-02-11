get_bg_tile_info(int tile_index)
{
	int offs = tile_index * 2;
	int code = videoram[offs + 1] + ((videoram[offs] & 0x07) << 8) + 2048 * gfxbank;
	int color = ((videoram[offs] & 0xf8) >> 3) + 32 * palettebank;

	SET_TILE_INFO(0, code, color, 0)
}
