get_bg2_tile_info(int tile_index)
{
	int tileno;
	int col;

	tileno = tbowl_bg2videoram[tile_index] | ((tbowl_bg2videoram[tile_index+0x1000] & 0x0f) << 8);
	tileno ^= 0x400;
	col = (tbowl_bg2videoram[tile_index+0x1000] & 0xf0) >> 4;

	SET_TILE_INFO(2,tileno,col,0)
}
