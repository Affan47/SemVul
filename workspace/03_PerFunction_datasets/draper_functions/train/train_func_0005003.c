draw_sprites(struct mame_bitmap *bitmap,const struct rectangle *cliprect)
{
int offs;

	for ( offs = 0 ; offs < (spriteram_size >> 1); offs += 4 )
	{
		int y		=	spriteram16[offs + 0];
		int x		=	spriteram16[offs + 1];
		int code	=	spriteram16[offs + 2];
		int attr	=	spriteram16[offs + 3];
		int flipx	=	code & 0x4000;
		int flipy	=	code & 0x8000;

		x = (x & 0xFF) - (x & 0x100);
		y = (y & 0xFF) - (y & 0x100);

		if (flipscreen)
		{
			x = 240 - x;		y = 240 - y;
			flipx = !flipx; 	flipy = !flipy;
		}

		drawgfx(bitmap,Machine->gfx[3],
				code & 0x3fff,
				attr >> 12,
				flipx, flipy,
				x,y,
				cliprect,TRANSPARENCY_PEN,15);

	}
}
