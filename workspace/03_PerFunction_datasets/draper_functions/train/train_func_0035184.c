draw_sprites( struct mame_bitmap *bitmap, const struct rectangle *cliprect, int priority )
{
	const unsigned char *finish = spriteram;
	const unsigned char *source = spriteram+0x60-4;
	const struct GfxElement *gfx = Machine->gfx[1];

	while( source>=finish )
	{
		int attributes = source[2];


		if( (attributes>>7) == priority )
		{
			int y;
			int color = (attributes>>4)&7;
			int flipx = attributes&0x01;
			int flipy = attributes&0x02;
			int height = (attributes&0x08) ? 2 : 1;
			int sx = source[0];
			int sy = 256 -16*height -source[1];
			int sprite_number = source[3] + ((attributes & 0x04) << 6);

			if (flip_screen_x)
			{
				sx = 240 - sx - 6;
				flipx = !flipx;
			}
			else
				sx -= 23;
			sx = ((sx + 8) & 0xff) - 8;
			if (flip_screen_y)
			{
				sy = 256 - 16*height - sy;
				flipy = !flipy;
			}
			sy -= 1;

			if (height == 2 && !flipy) sprite_number ^= 1;

			for (y = 0;y < height;y++)
			{
				drawgfx( bitmap,gfx,
						sprite_number ^ y,
						color,
						flipx,flipy,
						sx,sy + 16*y,
						cliprect,
						TRANSPARENCY_PEN,0 );
			}
		}
		source-=4;
	}
}
