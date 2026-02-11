get_tile_info(int tile_index)
{
	UINT16 code = ohmygod_videoram[2*tile_index+1];
	UINT16 attr = ohmygod_videoram[2*tile_index];
	SET_TILE_INFO(
			0,
			code,
			(attr & 0x0f00) >> 8,
			0)
}
