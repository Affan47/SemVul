draw_background( struct mame_bitmap *bitmap ){
	const UINT8 *source = videoram;
	const struct GfxElement *gfx = Machine->gfx[1];
	int sx,sy;
	int base = 0;
	if( mrflea_gfx_bank&0x04 ) base |= 0x400;
	if( mrflea_gfx_bank&0x10 ) base |= 0x200;
	for( sy=0; sy<256; sy+=8 ){
		for( sx=0; sx<256; sx+=8 ){
			int tile_number = base+source[0]+source[0x400]*0x100;
			source++;
			drawgfx( bitmap, gfx,
				tile_number,
				0,
				0,0,
				sx,sy,
				0,
				TRANSPARENCY_NONE,0 );
		}
	}
}
