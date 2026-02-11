exprraid_draw_sprites( struct mame_bitmap *bitmap )
{
	int offs;

	for (offs = 0;offs < spriteram_size;offs += 4)
	{
		int attr = spriteram[offs + 1];
		int code = spriteram[offs + 3] + ((attr & 0xe0) << 3);
		int color = (attr & 0x03) + ((attr & 0x08) >> 1);
		int flipx = (attr & 0x04);
		int flipy = 0;
		int sx = ((248 - spriteram[offs + 2]) & 0xff) - 8;
		int sy = spriteram[offs];

		if (flip_screen)
		{
			sx = 240 - sx;
			sy = 240 - sy;
			flipx = !flipx;
			flipy = !flipy;
		}

		drawgfx(bitmap, Machine->gfx[1],
			code, color,
			flipx, flipy,
			sx, sy,
			0, TRANSPARENCY_PEN, 0);


		if (attr & 0x10)
		{
			drawgfx(bitmap,Machine->gfx[1],
				code + 1, color,
				flipx, flipy,
				sx, sy + (flip_screen ? -16 : 16),
				0, TRANSPARENCY_PEN, 0);
		}
	}
}
