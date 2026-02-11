draw_sprites(struct mame_bitmap *bitmap, const struct rectangle *cliprect)
{
	int i;

	for (i = 0; i < spriteram_size ; i += 8)
	{
		int y		=	 240 - spriteram[i+1];
		int code	=	(spriteram[i+3] & 0x3f) + (spriteram[i+2] << 6);
		int x		=	 spriteram[i+5]         + (spriteram[i+6] << 8);
		int attr	=	 spriteram[i+7];

		int flipx	=	0;
		int flipy	=	0;

		x -= 0x4a/2;
		if (flip_screen)
		{
			y = 240 - y;
			flipx = !flipx;
			flipy = !flipy;
		}

		drawgfx(bitmap,Machine->gfx[0],
				code,
				attr & 0x0f,
				flipx,flipy,
				x,y,
				cliprect,TRANSPARENCY_PEN,15 );
	}
}
