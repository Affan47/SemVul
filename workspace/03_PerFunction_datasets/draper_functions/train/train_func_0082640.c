flower_drawtextlayer( struct mame_bitmap *bitmap, const struct rectangle *cliprect )
{
	int offs,sx,sy;

	unsigned char *vr = memory_region(REGION_CPU1);

	for (offs = 0;offs < 0x400;offs++)
	{
		sx = offs%32;
		sy = offs/32-2;

		if(sy<0)
		{
			int tt;
			tt=sx;
			sx=34+sy;
			sy=tt-2;
		}

		drawgfx(bitmap,Machine->gfx[0],
				vr[0xe000+offs],
				0,
				0,0,
				8*sx,8*sy,
				cliprect,TRANSPARENCY_PEN,0);
	}

}
