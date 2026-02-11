get_fg_tile_info(int tile_index)
{
	unsigned char attr = ddrible_fg_videoram[tile_index];
	int num = ddrible_fg_videoram[tile_index + 0x400] +
			((attr & 0xc0) << 2) + ((attr & 0x20) << 5) + ((charbank[0] & 2) << 10);
	SET_TILE_INFO(
			0,
			num,
			0,
			TILE_FLIPYX((attr & 0x30) >> 4))
}
