get_bg_tile_info(int tile_index)
{


	static int split_table[16] =
	{
		3,0,2,2,
		0,1,0,0,
		0,0,0,0,
		0,0,0,0
	};
	unsigned char attr = scroll_ram[2*tile_index + 1];
	int color = (attr & 0x78) >> 3;
	SET_TILE_INFO(
			1,
			scroll_ram[2*tile_index] + ((attr & 0x07) << 8),
			color,
			TILE_SPLIT(split_table[color]) | ((attr & 0x80) ? TILE_FLIPX : 0))
}
