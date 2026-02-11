bagman_draw_sprites( struct mame_bitmap *bitmap )
{
	int offs;

	for (offs = spriteram_size - 4;offs >= 0;offs -= 4)
	{
		int sx,sy,flipx,flipy;


		sx = spriteram[offs + 3];
		sy = 240 - spriteram[offs + 2];
		flipx = spriteram[offs] & 0x40;
		flipy = spriteram[offs] & 0x80;
		if (flip_screen_x)
		{
			sx = 240 - sx +1;
			flipx = !flipx;
		}
		if (flip_screen_y)
		{
			sy = 240 - sy;
			flipy = !flipy;
		}

		if (spriteram[offs + 2] && spriteram[offs + 3])
			drawgfx(bitmap,Machine->gfx[1],
					(spriteram[offs] & 0x3f) + 2 * (spriteram[offs + 1] & 0x20),
					spriteram[offs + 1] & 0x1f,
					flipx,flipy,
					sx,sy+1,
					&Machine->visible_area,TRANSPARENCY_PEN,0);
	}
}
