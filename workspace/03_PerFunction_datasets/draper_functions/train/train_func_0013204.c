draw_missiles(struct mame_bitmap *bitmap, const struct rectangle *cliprect,
						int missile_y_adjust, int missile_y_adjust_flip_screen,
						unsigned char *missile_ram, int interleave)
{
	int i,offs;


	for (i = 0, offs = 0; i < 8; i++, offs += 4*interleave)
	{
		int sx,sy;

		sy = 255 - missile_ram[offs + 0*interleave];
		sx = 255 - missile_ram[offs + 2*interleave];
		if (flip_screen)
		{
			sx = 240 - sx;
			sy = 240 - sy + missile_y_adjust_flip_screen;
		}
		sy -= missile_y_adjust;
		drawgfx(bitmap,Machine->gfx[4],
				0,32 + ((color_missiles >> 4) & 7), 0,0, sx,sy,
				cliprect, TRANSPARENCY_PEN, 0);

		sy = 255 - missile_ram[offs + 1*interleave];
		sx = 255 - missile_ram[offs + 3*interleave];
		if (flip_screen)
		{
			sx = 240 - sx;
			sy = 240 - sy + missile_y_adjust_flip_screen;
		}
		sy -= missile_y_adjust;
		drawgfx(bitmap,Machine->gfx[4],
				0,32 + (color_missiles & 7), 0,0, sx,sy,
				cliprect, TRANSPARENCY_PEN, 0);
	}
}
