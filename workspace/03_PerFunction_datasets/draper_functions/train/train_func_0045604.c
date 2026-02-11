rohga_drawsprites(struct mame_bitmap *bitmap, const data16_t *spriteptr)
{
	int offs;

	for (offs = 0x400-4;offs >= 0;offs -= 4)
	{
		int x,y,sprite,colour,multi,fx,fy,inc,flash,mult,pri=0;
		sprite = spriteptr[offs+1];
		if (!sprite) continue;

		x = spriteptr[offs+2];


		switch (x&0xc000) {
		case 0x0000: pri=0; break;
		case 0x4000: pri=0xf0; break;
		case 0x8000: pri=0xf0|0xcc; break;
		case 0xc000: pri=0xf0|0xcc; break;
		}

		y = spriteptr[offs];
		flash=y&0x1000;
		if (flash && (cpu_getcurrentframe() & 1)) continue;
		colour = (x >> 9) &0xf;

		fx = y & 0x2000;
		fy = y & 0x4000;
		multi = (1 << ((y & 0x0600) >> 9)) - 1;

		x = x & 0x01ff;
		y = y & 0x01ff;
		if (x >= 320) x -= 512;
		if (y >= 256) y -= 512;

		sprite &= ~multi;
		if (fy)
			inc = -1;
		else
		{
			sprite += multi;
			inc = 1;
		}

		if (flip_screen) {
			x=304-x;
			y=240-y;
			if (fx) fx=0; else fx=1;
			if (fy) fy=0; else fy=1;
			mult=-16;
		}
		else mult=+16;

		while (multi >= 0)
		{
			pdrawgfx(bitmap,Machine->gfx[3],
					sprite - multi * inc,
					colour,
					fx,fy,
					x,y + mult * multi,
					&Machine->visible_area,TRANSPARENCY_PEN,0,pri);

			multi--;
		}
	}
}
