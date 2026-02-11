cosmica_draw_starfield(struct mame_bitmap *bitmap)
{
	UINT8 y = 0;
	UINT8 map = 0;
	data8_t *PROM = memory_region(REGION_USER2);


	while (1)
	{
		int va  =  y       & 0x01;
		int vb  = (y >> 1) & 0x01;


		UINT8 x = 0;

		while (1)
		{
			UINT8 x1;
			int hc, hb_;


			if (flip_screen)
				x1 = x - cpu_getcurrentframe();
			else
				x1 = x + cpu_getcurrentframe();


			hc  = (x1 >> 2) & 0x01;
			hb_ = (x  >> 5) & 0x01;


			if ((x1 & 0x1f) == 0)
			{

				map = PROM[(x1 >> 5) | (y >> 1 << 3)];
			}


			if ((!(hc & va) & (vb ^ hb_)) &&
			    (((x1 ^ map) & (hc | 0x1e)) == 0x1e))
			{

				int col = (map >> 7) | ((map >> 5) & 0x02) | ((map >> 3) & 0x04);

				plot_pixel(bitmap, x, y, Machine->pens[col]);
			}


			x++;
			if (x == 0)  break;
		}


		y++;
		if (y == 0)  break;
	}
}
