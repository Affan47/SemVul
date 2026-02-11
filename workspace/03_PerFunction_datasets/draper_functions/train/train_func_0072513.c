update_smoothing(int bgtilerow, int first, int last)
{
	UINT8 *prom = memory_region(REGION_PROMS) + smooth_table * 0x100;
	UINT8 bgscan[2][256];
	UINT8 *bgcurr = bgscan[0], *bglast = bgscan[1];
	int xstart, xstop, x, y;


	xstart = first * 16 - 1;
	xstop = last * 16 + 15;


	extract_scanline8(bgbitmap, 0, ((bgtilerow * 16 - 1) & 0x1ff) / 2, 256, bgcurr);


	for (y = 0; y <= 16; y++)
	{
		int curry = (bgtilerow * 16 + y) & 0x1ff;


		UINT8 *bgtemp = bgcurr;
		bgcurr = bglast;
		bglast = bgtemp;


		extract_scanline8(bgbitmap, 0, curry / 2, 256, bgcurr);


		for (x = xstart; x <= xstop; x++)
		{
			int tr = bglast[((x + 1) & 0x1ff) / 2];
			int br = bgcurr[((x + 1) & 0x1ff) / 2];


			if (x & 1)
			{
				int tl = bglast[(x & 0x1ff) / 2];
				int bl = bgcurr[(x & 0x1ff) / 2];
				int mixt = prom[16 * tl + tr];
				int mixb = prom[16 * bl + br];
				plot_pixel(bgexbitmap, x & 0x1ff, curry, prom[0x400 + 16 * mixt + mixb]);
			}
			else
				plot_pixel(bgexbitmap, x & 0x1ff, curry, prom[0x400 + 16 * tr + br]);
		}
	}
}
