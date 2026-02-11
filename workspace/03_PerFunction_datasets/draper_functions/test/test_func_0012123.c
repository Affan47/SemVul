draw_status( struct mame_bitmap *bitmap, const struct rectangle *cliprect )
{
	const unsigned char *base = videoram+0x400;
	const struct GfxElement *gfx = Machine->gfx[0];
	int row;
	for( row=0; row<4; row++ )
	{
		int sy,sx = (row&1)*8;
		const unsigned char *source = base + (row&1)*32;
		if( row>1 )
		{
			sx+=256+16;
		}
		else
		{
			source+=30*32;
		}

		for( sy=0; sy<256; sy+=8 )
		{
			int tile_number = *source++;
			drawgfx( bitmap, gfx,
			    tile_number, tile_number>>5,
			    0,0,
			    sx,sy,
			    cliprect,
			    TRANSPARENCY_NONE, 0xf );
		}
	}
}
