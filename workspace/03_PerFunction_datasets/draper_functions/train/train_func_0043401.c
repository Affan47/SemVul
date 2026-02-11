draw_sprites( struct mame_bitmap *bitmap )
{
	const data8_t *source = portrait_spriteram;
	const data8_t *finish = source + 0x200;
	while( source<finish )
	{
		int sy      = source[0];
		int sx      = source[1];
		int attr    = source[2];


		int tilenum = source[3];
		int color = 0;
		int flip = attr&0x20;
		if( attr&0x04 ) sx |= 0x100;
		if( attr&0x08 ) sy |= 0x100;

		sx += (source-portrait_spriteram)-8;
		sx &= 0x1ff;

		sy = (512-64)-sy;


		drawgfx(bitmap,Machine->gfx[0],
			tilenum,color,
			0,flip,
			sx,sy,
			NULL,TRANSPARENCY_PEN,0 );

		source+=0x10;
	}
}
