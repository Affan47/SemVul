get_bg0_tile_info(int tile_index)
{


	data16_t *tilebase;
	int tileno, colbank, flipx;
	tilebase =  &wwfsstar_bg0_videoram[tile_index*2];
	tileno =  (tilebase[1] & 0x00ff) | ((tilebase[0] & 0x000f) << 8);
	colbank = (tilebase[0] & 0x0070) >> 4;
	flipx   = (tilebase[0] & 0x0080) >> 7;
	SET_TILE_INFO(
			2,
			tileno,
			colbank,
			flipx ? TILE_FLIPX : 0)
}
