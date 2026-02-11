get_bg_tile_info(int tile_index)
{
	int code, color;

	code = vulgus_bgvideoram[tile_index];
	color = vulgus_bgvideoram[tile_index + 0x400];
	SET_TILE_INFO(
			1,
			code + ((color & 0x80) << 1),
			(color & 0x1f) + (0x20 * vulgus_palette_bank),
			TILE_FLIPYX((color & 0x60) >> 5))
}
