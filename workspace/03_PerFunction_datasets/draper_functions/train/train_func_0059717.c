get_back_tile_info(int tile_index)
{
	int tile=legionna_back_data[tile_index];
	int color=(tile>>12)&0xf;

	tile &= 0xfff;
	tile |= gfx_bank;

	SET_TILE_INFO(1,tile,color,0)
}
