rshark_draw_sprites(struct mame_bitmap *bitmap)
{
	int offs;

	for (offs = 0;offs < spriteram_size/2;offs += 8)
	{
		if (buffered_spriteram16[offs] & 0x0001)
		{
			int sx,sy,code,color;
			int flipx=0,flipy=0,width,height,x,y;

			sx = buffered_spriteram16[offs+4] & 0x01ff;
			sy = (INT16)buffered_spriteram16[offs+6];
			code = buffered_spriteram16[offs+3];
			color = buffered_spriteram16[offs+7];
			width = buffered_spriteram16[offs+1] & 0x000f;
			height = (buffered_spriteram16[offs+1] & 0x00f0) >> 4;

			if (flip_screen)
			{
				sx = 498-16*width - sx;
				sy = 240-16*height - sy;
				flipx = !flipx;
				flipy = !flipy;
			}

			for (y = 0;y <= height;y++)
			{
				for (x = 0;x <= width;x++)
				{
					drawgfx(bitmap,Machine->gfx[0],
							code,
							color,
							flipx,flipy,
							flipx ? sx + 16*(width-x) : sx + 16*x,
							flipy ? sy + 16*(height-y) : sy + 16*y,
							&Machine->visible_area,TRANSPARENCY_PEN,15);

					code++;
				}
			}
		}
	}
}
