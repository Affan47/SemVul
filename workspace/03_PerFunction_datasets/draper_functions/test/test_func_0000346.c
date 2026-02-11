tnk3_draw_text( struct mame_bitmap *bitmap, int bank, unsigned char *source )
{
	const struct GfxElement *gfx = Machine->gfx[0];
	struct rectangle *clip = &Machine->visible_area;

	int tile_number, color, sx, sy;
	int x, y;

	for(x=0; x<32; x++) for(y=0; y<32; y++)
	{
		tile_number = source[(x<<5)+y];

		if(tile_number == 0x20 || tile_number == 0xff) continue;

		if(bank == -1) color = 8;
		else
		{
			color = tile_number >> 5;
			tile_number |= bank << 8;
		}
		sx = (x+2) << 3;
		sy = (y+1) << 3;

		drawgfx(bitmap,gfx,tile_number,color,0,0,sx,sy,clip,TRANSPARENCY_PEN,15);
	}
}
