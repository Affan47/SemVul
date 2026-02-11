unico_draw_sprites(struct mame_bitmap *bitmap,const struct rectangle *cliprect)
{
	int offs;


	for ( offs = (spriteram_size-8)/2; offs >= 0 ; offs -= 8/2 )
	{
		int x, startx, endx, incx;

		int	sx			=	spriteram16[ offs + 0 ];
		int	sy			=	spriteram16[ offs + 1 ];
		int	code		=	spriteram16[ offs + 2 ];
		int	attr		=	spriteram16[ offs + 3 ];

		int	flipx		=	attr & 0x020;
		int	flipy		=	attr & 0x040;

		int dimx		=	((attr >> 8) & 0xf) + 1;

		int priority	=	((attr >> 12) & 0x3);
		int pri_mask;

		switch( priority )
		{
			case 0:		pri_mask = 0xfe;	break;
			case 1:		pri_mask = 0xf0;	break;
			case 2:		pri_mask = 0xfc;	break;
			default:
			case 3:		pri_mask = 0x00;
		}

		sx	+=	sprites_scrolldx;
		sy	+=	sprites_scrolldy;

		sx	=	(sx & 0x1ff) - (sx & 0x200);
		sy	=	(sy & 0x1ff) - (sy & 0x200);

		if (flipx)	{	startx = sx+(dimx-1)*16;	endx = sx-16;		incx = -16;	}
		else		{	startx = sx;				endx = sx+dimx*16;	incx = +16;	}

		for (x = startx ; x != endx ; x += incx)
		{
			pdrawgfx(	bitmap, Machine->gfx[0],
						code++,
						attr & 0x1f,
						flipx, flipy,
						x, sy,
						cliprect, TRANSPARENCY_PEN,0x00,
						pri_mask	);
		}
	}
}
