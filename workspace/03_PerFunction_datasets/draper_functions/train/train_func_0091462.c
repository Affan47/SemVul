get_bac0_tile_info( int tile_index )
{
	int tile,color,offs=tile_index<<1;

	tile=(dec8_pf0_data[offs]<<8) | dec8_pf0_data[offs+1];
	color=tile >> 12;
	if (color>7 && game_uses_priority) tile_info.priority=1; else tile_info.priority=0;

	SET_TILE_INFO(
			2,
			tile&0xfff,
			color&gfx_mask,
			0)
}
