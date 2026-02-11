get_pf2_tile_info(int tile_index)
{
	int tile,color,pri;
	tile_index = 4*tile_index + pf2_vram_ptr;

	tile=m92_vram_data[tile_index]+(m92_vram_data[tile_index+1]<<8)+((m92_vram_data[tile_index+3]&0x80)<<9);
	color=m92_vram_data[tile_index+2];
	if (m92_vram_data[tile_index+3]&1) pri = 2;
	else if (color&0x80) pri = 1;
	else pri = 0;

	SET_TILE_INFO(
			0,
			tile,
			color&0x7f,
			TILE_FLIPYX((m92_vram_data[tile_index+3] & 0x6)>>1) | TILE_SPLIT(pri))
}
