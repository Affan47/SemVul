devzone_draw_grid(struct mame_bitmap *bitmap)
{
	UINT8 y;
	data8_t *horz_PROM = memory_region(REGION_USER2);
	data8_t *vert_PROM = memory_region(REGION_USER3);
	offs_t horz_addr = 0;

	UINT8 count = 0;
	UINT8 horz_data = 0;
	UINT8 vert_data;


	for (y = 32; y < 224; y++)
	{
		UINT8 x = 0;


		while (1)
		{
			int x1;


			vert_data = vert_PROM[x >> 3];


			if (count == 0)
			{
				count = horz_PROM[horz_addr++];
			}

			count++;

			if (count == 0)
			{
				horz_data = horz_PROM[horz_addr++];
			}


			for (x1 = 0; x1 < 8; x1++)
			{
				if (!(vert_data & horz_data & 0x80))
				{
					pen_t pen = Machine->pens[4];

					if (flip_screen)
						plot_pixel(bitmap, 255-x, 255-y, pen);
					else
						plot_pixel(bitmap,     x,     y, pen);
				}

				horz_data = (horz_data << 1) | 0x01;
				vert_data = (vert_data << 1) | 0x01;

				x++;
			}


			if (x == 0)  break;
		}
	}
}
