draw_grid(struct mame_bitmap *bitmap)
{
	const UINT8 *table = memory_region(REGION_GFX3);
	int x,y,counter;

	counter = flip_screen ? 0x000 : 0x400;

	x = Machine->visible_area.min_x;
	y = Machine->visible_area.min_y;
	while (y <= Machine->visible_area.max_y)
	{
		x = 4 * (table[counter] & 0x7f);
		if (x >= Machine->visible_area.min_x &&
				x <= Machine->visible_area.max_x)
		{
			if (table[counter] & 0x80)
			{
				if (rand() & 1)
					plot_pixel(bitmap,x,y,Machine->pens[256]);
			}
			else if (grid_on)
				plot_pixel(bitmap,x,y,Machine->pens[257]);
		}

		counter++;

		if (x >= 4 * (table[counter] & 0x7f))
			y++;
	}
}
