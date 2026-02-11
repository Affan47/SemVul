draw_fg(struct mame_bitmap *bitmap)
{
	int offs;


	for (offs = 0;offs < 0x400;offs++)
	{
		int sx = offs % 32;
		int sy = offs / 32;

		int transp = (bg_on && sx >= 22) ? TRANSPARENCY_NONE : TRANSPARENCY_PEN;

		int code = videoram[offs];

		if (flip_screen_x) sx = 31 - sx;
		if (flip_screen_y) sy = 31 - sy;

		drawgfx(bitmap,Machine->gfx[0],
				code,
				0,
				flip_screen_x,flip_screen_y,
				8*sx,8*sy,
				&Machine->visible_area,transp,0);
	}
}
