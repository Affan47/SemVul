tagteam_draw_sprites( struct mame_bitmap *bitmap )
{
	int offs;

	for (offs = 0; offs < 0x20; offs += 4)
	{
		int spritebank = (videoram[offs] & 0x30) << 4;
		int code = videoram[offs + 1] + 256 * spritebank;
		int color = 1 + 2 * palettebank;
		int flipx = videoram[offs] & 0x04;
		int flipy = videoram[offs] & 0x02;
		int sx = 240 - videoram[offs + 3];
		int sy = 240 - videoram[offs + 2];

		if (!(videoram[offs] & 0x01)) continue;

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
			&Machine->visible_area,
			TRANSPARENCY_PEN, 0);


		code = videoram[offs + 0x20] + 256 * spritebank;
		color = palettebank;
		sy += (flip_screen ? -256 : 256);

		drawgfx(bitmap, Machine->gfx[1],
			code, color,
			flipx, flipy,
			sx, sy,
			&Machine->visible_area,
			TRANSPARENCY_PEN, 0);
	}
}
