powerins_draw_sprites(struct mame_bitmap *bitmap,const struct rectangle *cliprect)
{
	data16_t *source = spriteram16 + 0x8000/2;
	data16_t *finish = spriteram16 + 0x9000/2;

	int screen_w	=	Machine->drv->screen_width;
	int screen_h	=	Machine->drv->screen_height;

	for ( ; source < finish; source += 16/2 )
	{
		int x,y,inc;

		int	attr	=	source[ 0x0/2 ];
		int	size	=	source[ 0x2/2 ];
		int	code	=	source[ 0x6/2 ];
		int	sx		=	source[ 0x8/2 ];
		int	sy		=	source[ 0xc/2 ];
		int	color	=	source[ 0xe/2 ];

		int	flipx	=	size & 0x1000;
		int	flipy	=	0;

		int	dimx	=	((size >> 0) & 0xf ) + 1;
		int	dimy	=	((size >> 4) & 0xf ) + 1;

		if (!(attr&1)) continue;

		SIGN_EXTEND_POS(sx)
		SIGN_EXTEND_POS(sy)


		if (flip_screen)
		{	sx = screen_w - sx - dimx*16 - 32;	flipx = !flipx;
			sy = screen_h - sy - dimy*16;		flipy = !flipy;
			code += dimx*dimy-1;			inc = -1;	}
		else
		{	sx += 32;						inc = +1;	}

		code = (code & 0x7fff) + ( (size & 0x0100) << 7 );

		for (x = 0 ; x < dimx ; x++)
		{
			for (y = 0 ; y < dimy ; y++)
			{
				drawgfx(bitmap,Machine->gfx[2],
						code,
						color,
						flipx, flipy,
						sx + x*16,
						sy + y*16,
						cliprect,TRANSPARENCY_PEN,15);

				code += inc;
			}
		}


	}
}
