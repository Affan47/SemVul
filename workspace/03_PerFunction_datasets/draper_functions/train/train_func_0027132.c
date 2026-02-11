draw_sprites(struct mame_bitmap *bitmap, const struct rectangle *cliprect)
{
	int offs;


	for (offs = 0;offs < 16;offs++)
	{
		int sx,sy,code,color,flipx,flipy;


		sx = espial_spriteram_1[offs + 16];
		sy = espial_spriteram_2[offs];
		code = espial_spriteram_1[offs] >> 1;
		color = espial_spriteram_2[offs + 16];
		flipx = espial_spriteram_3[offs] & 0x04;
		flipy = espial_spriteram_3[offs] & 0x08;

		if (flipscreen)
		{
			flipx = !flipx;
			flipy = !flipy;
		}
		else
		{
			sy = 240 - sy;
		}

		if (espial_spriteram_1[offs] & 1)
		{
			if (flipscreen)
			{
				drawgfx(bitmap,Machine->gfx[1],
						code,color,
						flipx,flipy,
						sx,sy + 16,
						cliprect,TRANSPARENCY_PEN,0);
				drawgfx(bitmap,Machine->gfx[1],
						code + 1,
						color,
						flipx,flipy,
						sx,sy,
						cliprect,TRANSPARENCY_PEN,0);
			}
			else
			{
				drawgfx(bitmap,Machine->gfx[1],
						code,color,
						flipx,flipy,
						sx,sy - 16,
						cliprect,TRANSPARENCY_PEN,0);
				drawgfx(bitmap,Machine->gfx[1],
						code + 1,color,
						flipx,flipy,
						sx,sy,
						cliprect,TRANSPARENCY_PEN,0);
			}
		}
		else
		{
			drawgfx(bitmap,Machine->gfx[1],
					code,color,
					flipx,flipy,
					sx,sy,
					cliprect,TRANSPARENCY_PEN,0);
		}
	}
}
