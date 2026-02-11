senjyo_bg1_tile_info(int tile_index)
{
	unsigned char code = senjyo_bg1videoram[tile_index];
	SET_TILE_INFO(
			1,
			code,
			(code & 0x70) >> 4,
			0)
}
