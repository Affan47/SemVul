draw_sprites(struct mame_bitmap *bitmap, const struct rectangle *cliprect, int gfxbank, unsigned char *sprite_ram)
{
	int offs,sx,sy,tile,palette;

	for (offs = 0 ;offs < spriteram_size; offs+=4)
	{
		sx = sprite_ram[offs];
		sy = 240-sprite_ram[offs+1];

		if (flip_screen)
		{
			sx = 248 - sx;
			sy = 248 - sy;
		}

		if ((sprite_ram[offs+1] >> 3) && (sx < 248))
		{
			tile	 = ((sprite_ram[offs+3])+((sprite_ram[offs+2] & 7) << 8));
			tile	+= tile;
			palette	 = sprite_ram[offs+2] >> 3;

			drawgfx(bitmap,Machine->gfx[gfxbank],
						tile,
						palette,
						flip_screen,flip_screen,
						sx,sy,
						cliprect,
						TRANSPARENCY_PEN, 0);
			drawgfx(bitmap,Machine->gfx[gfxbank],
						tile+1,
						palette,
						flip_screen,flip_screen,
						sx,sy + (flip_screen ? -8 : 8),
						cliprect,
						TRANSPARENCY_PEN, 0);
		}
	}
}
