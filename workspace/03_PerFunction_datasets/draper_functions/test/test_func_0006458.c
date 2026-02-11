prt_map_aux(void)
{
	byte a;
	char c;
	byte ta;
	char tc;
	grid_data g;

	int y, x;
	int vy, vx;
	int ty, tx;

	int j;


	for (j = 0; j < ANGBAND_TERM_MAX; j++)
	{
		term *t = angband_term[j];


		if (!t) continue;


		if (!(op_ptr->window_flag[j] & (PW_MAP))) continue;


		ty = t->offset_y + (t->hgt / tile_height);
		tx = t->offset_x + (t->wid / tile_width);


		for (y = t->offset_y, vy = 0; y < ty; vy++, y++)
		{
		        if (vy + tile_height - 1 >= t->hgt) continue;
			for (x = t->offset_x, vx = 0; x < tx; vx++, x++)
			{

				if (!in_bounds(y, x)) continue;

				if (vx + tile_width - 1 >= t->wid) continue;


				map_info(y, x, &g);
				grid_data_as_text(&g, &a, &c, &ta, &tc);
				Term_queue_char(t, vx, vy, a, c, ta, tc);

				if ((tile_width > 1) || (tile_height > 1))
					Term_big_queue_char(t, vx, vy, 255, -1, 0, 0);
			}
		}
	}
}
