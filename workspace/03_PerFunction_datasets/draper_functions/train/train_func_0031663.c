init_star_field(void)
{
	int generator;
	int count,x,y;

	generator = 0;


	for (count = 0;count < RNG_PERIOD;count++)
	{
		int bit1,bit2;

		generator <<= 1;
		bit1 = (~generator >> 17) & 1;
		bit2 = (generator >> 5) & 1;

		if (bit1 ^ bit2) generator |= 1;

		rng[count] = generator & 0x1ffff;
	}


	count = 0;
	for (y = 0;y < MAX_LINES;y++)
	{
		for (x = -16;x < CLOCKS_PER_LINE-16;x++)
		{
			if (x >= Machine->visible_area.min_x &&
				x <= Machine->visible_area.max_x &&
				y >= Machine->visible_area.min_y &&
				y <= Machine->visible_area.max_y)
			{
				if ((rng[count] & 0x1fe00) == 0x0fe00)
					star[x+SCREEN_WIDTH*y] = 1;
				else
					star[x+SCREEN_WIDTH*y] = 0;
			}

			count++;
		}
	}


	for (count = 0;count < RNG_PERIOD;count++)
	{
		int r;

		r = rng[count];
		rng[count] = (((r >> 12) & 1) << 3) +
					 (((r >>  8) & 1) << 2) +
					 (((r >>  4) & 1) << 1) +
					 (((r >>  0) & 1) << 0);
	}
}
