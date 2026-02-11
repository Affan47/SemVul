update_maps(game_event_type type, game_event_data *data, void *user)
{
	term *t = user;


	if (data->point.x == -1 && data->point.y == -1)
	{
		prt_map();
	}

	else
	{
		grid_data g;
		byte a, ta;
		wchar_t c, tc;

		int ky, kx;
		int vy, vx;


		ky = data->point.y - t->offset_y;
		kx = data->point.x - t->offset_x;

		if (t == angband_term[0])
		{

			if ((ky < 0) || (ky >= SCREEN_HGT)) return;


			if ((kx < 0) || (kx >= SCREEN_WID)) return;


			vy = ky + ROW_MAP;
			vx = kx + COL_MAP;

		      if (tile_width > 1)
		      {
			      vx += (tile_width - 1) * kx;
		      }
		      if (tile_height > 1)
		      {
			      vy += (tile_height - 1) * ky;
		      }
		}
		else
		{
			if (tile_width > 1)
			{
			        kx += (tile_width - 1) * kx;
			}
			if (tile_height > 1)
			{
			        ky += (tile_height - 1) * ky;
			}


			if ((ky < 0) || (ky >= t->hgt)) return;
			if ((kx < 0) || (kx >= t->wid)) return;


			vy = ky;
			vx = kx;
		}


		map_info(data->point.y, data->point.x, &g);
		grid_data_as_text(&g, &a, &c, &ta, &tc);
		Term_queue_char(t, vx, vy, a, c, ta, tc);
#if 0

		Term_queue_char(t, vx, vy, TERM_L_GREEN, c, ta, tc);
#endif

		if ((tile_width > 1) || (tile_height > 1))
		{
		        Term_big_queue_char(t, vx, vy, a, c, TERM_WHITE, ' ');
		}
	}
}
