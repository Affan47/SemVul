redraw_bitmap(void)
{
	int x, y;
	int screen_addr0_save, screen_addr1_save, screen_inc_enable0_save, screen_inc_enable1_save;


	screen_addr0_save = ccastles_screen_addr[0];
	screen_addr1_save = ccastles_screen_addr[1];

	screen_inc_enable0_save = ccastles_screen_inc_enable[0];
	screen_inc_enable1_save = ccastles_screen_inc_enable[1];

	ccastles_screen_inc_enable[0] = ccastles_screen_inc_enable[1] = 1;


	for (y = 0; y < 256; y++)
	{
		ccastles_screen_addr[1] = y;

		for (x = 0; x < 256; x++)
		{
			ccastles_screen_addr[0] = x;

			ccastles_bitmode_w(0, ccastles_bitmode_r(0));
		}
	}


	ccastles_screen_addr[0] = screen_addr0_save;
	ccastles_screen_addr[1] = screen_addr1_save;

	ccastles_screen_inc_enable[0] = screen_inc_enable0_save;
	ccastles_screen_inc_enable[1] = screen_inc_enable1_save;
}
