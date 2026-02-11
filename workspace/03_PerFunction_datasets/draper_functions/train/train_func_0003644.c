draw_sprites( struct mame_bitmap *bitmap, const struct rectangle *cliprect, int priority )
{
	int offs;

	for (offs = 0;offs < spriteram_size/2;offs += 4)
	{
		int code = buffered_spriteram16[offs+1];
		int flipx = code & 0x2000;
		int flipy = code & 0x1000;
		int color = (buffered_spriteram16[offs+2]>>8)&0x1f;
		int sx = buffered_spriteram16[offs+3];
		int sy = sprite_offy+240-(buffered_spriteram16[offs+0]&0x1ff);

		if (flip_screen) {
			sx = 320 - sx + 176;
			sy = 240 - sy + 1;
			flipx = !flipx;
			flipy = !flipy;
		}

		if (((buffered_spriteram16[offs+0] & 0x3000) >> 12) == priority)
		{
			drawgfx(bitmap,Machine->gfx[3],
				code & 0xfff,
				color,
 				flipx,flipy,
				sx,sy,
				cliprect,TRANSPARENCY_PEN,15);
		}
	}
}
