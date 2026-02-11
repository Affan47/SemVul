kchamp_draw_sprites( struct mame_bitmap *bitmap )
{
	int offs;

    for (offs = 0; offs < 0x100; offs += 4)
	{
		int attr = spriteram[offs + 2];
        int bank = 1 + ((attr & 0x60) >> 5);
        int code = spriteram[offs + 1] + ((attr & 0x10) << 4);
        int color = attr & 0x0f;
		int flipx = 0;
        int flipy = attr & 0x80;
        int sx = spriteram[offs + 3] - 8;
        int sy = 247 - spriteram[offs];

		if (flip_screen)
		{
			sx = 240 - sx;
			sy = 240 - sy;
			flipx = !flipx;
			flipy = !flipy;
		}

        drawgfx(bitmap, Machine->gfx[bank], code, color, flipx, flipy, sx, sy,
            &Machine->visible_area, TRANSPARENCY_PEN, 0);
	}
}
