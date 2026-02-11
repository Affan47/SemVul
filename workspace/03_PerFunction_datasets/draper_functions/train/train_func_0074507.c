forget_view(void)
{
	int i, g;

	int fast_view_n = view_n;
	u16b *fast_view_g = view_g;


	byte *fast_cave_info = &cave->info[0][0];


	if (!fast_view_n) return;


	for (i = 0; i < fast_view_n; i++)
	{
		int y, x;


		g = fast_view_g[i];


		y = GRID_Y(g);
		x = GRID_X(g);


		fast_cave_info[g] &= ~(CAVE_VIEW | CAVE_SEEN);


		cave_light_spot(cave, y, x);
	}


	fast_view_n = 0;


	view_n = fast_view_n;
}
