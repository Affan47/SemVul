oneshot_drawsprites( struct mame_bitmap *bitmap, const struct rectangle *cliprect )
{
	const UINT16 *source = oneshot_sprites;
	const UINT16 *finish = source+(0x1000/2);
	const struct GfxElement *gfx = Machine->gfx[1];

	int xpos,ypos;

	while( source<finish )
	{
		int blockx,blocky;
		int num = source[1] & 0xffff;
		int xsize = (source[2] & 0x000f)+1;
		int ysize = (source[3] & 0x000f)+1;

		ypos = source[3] & 0xff80;
		xpos = source[2] & 0xff80;

		ypos = ypos >> 7;
		xpos = xpos >> 7;


		if (source[0] == 0x0001) break;

		xpos -= 8;
		ypos -= 6;


		for (blockx = 0; blockx<xsize;blockx++) {
			for (blocky = 0; blocky<ysize;blocky++) {


				drawgfx(
						bitmap,
						gfx,
						num+(blocky*xsize)+blockx,
						1,
						0,0,
						xpos+blockx*8,ypos+blocky*8,
						cliprect,
						TRANSPARENCY_PEN,0
						);

				drawgfx(
						bitmap,
						gfx,
						num+(blocky*xsize)+blockx,
						1,
						0,0,
						xpos+blockx*8-0x200,ypos+blocky*8,
						cliprect,
						TRANSPARENCY_PEN,0
						);
			}
		}
		source += 0x4;
	}

}
