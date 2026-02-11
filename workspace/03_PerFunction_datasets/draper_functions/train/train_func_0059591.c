gotya_draw_sprites( struct mame_bitmap *bitmap )
{
	int offs;

	for (offs = 2; offs < 0x0e; offs += 2)
	{
		int code = spriteram[offs + 0x01] >> 2;
		int color = spriteram[offs + 0x11] & 0x0f;
		int sx = 256 - spriteram[offs + 0x10] + (spriteram[offs + 0x01] & 0x01) * 256;
		int sy = spriteram[offs + 0x00];

		if (flip_screen)
		{
			sy = 240 - sy;
		}

		drawgfx(bitmap,Machine->gfx[1],
			code, color,
			flip_screen_x, flip_screen_y,
			sx, sy,
			&Machine->visible_area,
			TRANSPARENCY_PEN, 0);
	}
}
