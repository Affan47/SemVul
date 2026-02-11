higemaru_draw_sprites( struct mame_bitmap *bitmap )
{
	int offs;

	for (offs = spriteram_size - 16;offs >= 0;offs -= 16)
	{
		int code,col,sx,sy,flipx,flipy;

		code = spriteram[offs] & 0x7f;
		col = spriteram[offs + 4] & 0x0f;
		sx = spriteram[offs + 12];
		sy = spriteram[offs + 8];
		flipx = spriteram[offs + 4] & 0x10;
		flipy = spriteram[offs + 4] & 0x20;
		if (flip_screen)
		{
			sx = 240 - sx;
			sy = 240 - sy;
			flipx = !flipx;
			flipy = !flipy;
		}

		drawgfx(bitmap,Machine->gfx[1],
				code,
				col,
				flipx,flipy,
				sx,sy,
				&Machine->visible_area,TRANSPARENCY_PEN,15);


		drawgfx(bitmap,Machine->gfx[1],
				code,
				col,
				flipx,flipy,
				sx - 256,sy,
				&Machine->visible_area,TRANSPARENCY_PEN,15);
	}
}
