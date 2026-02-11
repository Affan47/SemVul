sgladiat_draw_background( struct mame_bitmap *bitmap, int scrollx, int scrolly )
{
	const struct GfxElement *gfx = Machine->gfx[1];
	struct rectangle *clip = &Machine->visible_area;

	int tile_number, color, sx, sy;
	int offs, x, y;

	for(x = 0; x < 64; x++) for(y = 0; y < 32; y++)
	{
		offs = (x<<5)+y;
		tile_number = videoram[offs];

		if(tile_number != dirtybuffer[offs])
		{
			dirtybuffer[offs] = tile_number;

			color = 0;
			sx = x << 3;
			sy = y << 3;

			drawgfx(tmpbitmap,gfx,tile_number,color,0,0,sx,sy,0,TRANSPARENCY_NONE,0);
		}
	}
	copyscrollbitmap(bitmap,tmpbitmap,1,&scrollx,1,&scrolly,clip,TRANSPARENCY_NONE,0);
}
