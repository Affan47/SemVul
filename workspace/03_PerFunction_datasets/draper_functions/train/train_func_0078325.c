get_bg1_tile_info(int tile_index)
{
	UINT16 code = aerofgt_bg1videoram[tile_index];
	int bank = (code & 0x1800) >> 11;
	SET_TILE_INFO(
			0,
			(code & 0x07ff) + (gfxbank[bank] << 11),
			(code & 0xe000) >> 13,
			0)
}
