get_bg_tile_info(int tile_index)
{
	int code, color;

	tile_index = (tile_index & 0x0f) | ((tile_index & 0x01f0) << 1);

	code = c1942_bgvideoram[tile_index];
	color = c1942_bgvideoram[tile_index + 0x10];
	SET_TILE_INFO(
			1,
			code + ((color & 0x80) << 1),
			(color & 0x1f) + (0x20 * c1942_palette_bank),
			TILE_FLIPYX((color & 0x60) >> 5))
}
