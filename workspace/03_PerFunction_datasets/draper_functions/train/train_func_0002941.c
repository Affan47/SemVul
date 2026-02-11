find_hiding(int m_idx, int *yp, int *xp)
{
	monster_type *m_ptr = &mon_list[m_idx];

	int fy = m_ptr->fy;
	int fx = m_ptr->fx;

	int py = p_ptr->py;
	int px = p_ptr->px;

	int i, y, x, dy, dx, d, dis;
	int gy = 0, gx = 0, gdis = 999, min;

	const int *y_offsets, *x_offsets;


	min = distance(py, px, fy, fx) * 3 / 4 + 2;


	for (d = 1; d < 10; d++)
	{

		y_offsets = dist_offsets_y[d];
		x_offsets = dist_offsets_x[d];


		for (i = 0, dx = x_offsets[0], dy = y_offsets[0];
		     dx != 0 || dy != 0;
		     i++, dx = x_offsets[i], dy = y_offsets[i])
		{
			y = fy + dy;
			x = fx + dx;


			if (!in_bounds_fully(y, x)) continue;


			if (!cave_empty_bold(y, x)) continue;


			if (!player_has_los_bold(y, x) && (clean_shot(fy, fx, y, x)))
			{

				dis = distance(y, x, py, px);


				if (dis < gdis && dis >= min)
				{
					gy = y;
					gx = x;
					gdis = dis;
				}
			}
		}


		if (gdis < 999)
		{

			(*yp) = fy - gy;
			(*xp) = fx - gx;


			return (TRUE);
		}
	}


	return (FALSE);
}
