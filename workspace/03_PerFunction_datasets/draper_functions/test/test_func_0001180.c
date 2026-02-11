draw_chars(struct mame_bitmap *bitmap, int priority)
{
	int offs, transparency;


	transparency = (priority == 0) ? TRANSPARENCY_NONE : TRANSPARENCY_PEN;

	for (offs = 0; offs < videoram_size; offs++)
	{
		int code,sx,sy,col;
		UINT8 scroll;


		sy = (offs / 32);
		sx = (offs % 32);

		col = colorram[((sy & 0x1c) << 3) + sx];

		if ((col & 0x10) != priority)  continue;

		scroll = ~ambush_scrollram[sx];

		code = videoram[offs] | ((col & 0x60) << 3);

		if (flip_screen)
		{
			sx = 31 - sx;
			sy = 31 - sy;
			scroll = ~scroll - 1;
		}

		drawgfx(bitmap,Machine->gfx[0],
				code,
				(col & 0x0f) | ((*ambush_colorbank & 0x03) << 4),
				flip_screen,flip_screen,
				8*sx, (8*sy + scroll) & 0xff,
				&Machine->visible_area,transparency,0);
	}
}
