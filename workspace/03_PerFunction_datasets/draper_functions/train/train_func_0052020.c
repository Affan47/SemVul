speedspn_drawsprites( struct mame_bitmap *bitmap, const struct rectangle *cliprect )
{
	const struct GfxElement *gfx = Machine->gfx[1];
	data8_t *source = speedspn_vidram+ 0x1000;
	data8_t *finish = source + 0x1000;

	while( source<finish )
	{
		int xpos = source[0];
		int tileno = source[1];
		int attr = source[2];
		int ypos = source[3];
		int color;

		if (attr&0x10) xpos +=0x100;

		xpos = 0x1f8-xpos;
		tileno += ((attr & 0xe0) >> 5) * 0x100;
		color = attr & 0x0f;

		drawgfx(bitmap,gfx,
				tileno,
				color,
				0,0,
				xpos,ypos,
				cliprect,TRANSPARENCY_PEN,15);

		source +=4;
	}
}
