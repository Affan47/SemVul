get_tile_info(int tile_index)
{
	unsigned char attr = zaccaria_videoram[tile_index + 0x400];
	SET_TILE_INFO(
			0,
			zaccaria_videoram[tile_index] + ((attr & 0x03) << 8),
			((attr & 0x0c) >> 2) + ((zaccaria_attributesram[2 * (tile_index % 32) + 1] & 0x07) << 2),
			0)
}
