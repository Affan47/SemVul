madmotor_drawsprites(struct mame_bitmap *bitmap,const struct rectangle *cliprect,int pri_mask,int pri_val)
{
	int offs;

	offs = 0;
	while (offs < spriteram_size/2)
	{
		int sx,sy,code,color,w,h,flipx,flipy,incy,flash,mult,x,y;

		sy = spriteram16[offs];
		sx = spriteram16[offs+2];
		color = sx >> 12;

		flash=sx&0x800;

		flipx = sy & 0x2000;
		flipy = sy & 0x4000;
		h = (1 << ((sy & 0x1800) >> 11));
		w = (1 << ((sy & 0x0600) >>  9));


		code = spriteram16[offs+1] & 0x1fff;

		sx = sx & 0x01ff;
		sy = sy & 0x01ff;
		if (sx >= 256) sx -= 512;
		if (sy >= 256) sy -= 512;
		sx = 240 - sx;
		sy = 240 - sy;

		code &= ~(h-1);
		if (flipy)
			incy = -1;
		else
		{
			code += h-1;
			incy = 1;
		}

		if (flipscreen) {
			sy=240-sy;
			sx=240-sx;
			if (flipx) flipx=0; else flipx=1;
			if (flipy) flipy=0; else flipy=1;
			mult=16;
		}
		else mult=-16;

		for (x = 0;x < w;x++)
		{
			for (y = 0;y < h;y++)
			{
				if ((color & pri_mask) == pri_val &&
							(!flash || (cpu_getcurrentframe() & 1)))
					drawgfx(bitmap,Machine->gfx[3],
							code - y * incy + h * x,
							color,
							flipx,flipy,
							sx + mult * x,sy + mult * y,
							cliprect,TRANSPARENCY_PEN,0);
			}

			offs += 4;
			if (offs >= spriteram_size/2 ||
					spriteram16[offs] & 0x8000)
				 break;
		}
	}
}
