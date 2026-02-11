map_area(void)
{
	int i, x, y;
	int x1, x2, y1, y2;


	y1 = p_ptr->py - DETECT_DIST_Y;
	y2 = p_ptr->py + DETECT_DIST_Y;
	x1 = p_ptr->px - DETECT_DIST_X;
	x2 = p_ptr->px + DETECT_DIST_X;


	if (y1 < 0) y1 = 0;
	if (x1 < 0) x1 = 0;
	if (y2 > DUNGEON_HGT - 1) y2 = DUNGEON_HGT - 1;
	if (x2 > DUNGEON_WID - 1) x2 = DUNGEON_WID - 1;


	for (y = y1; y < y2; y++)
	{
		for (x = x1; x < x2; x++)
		{

			if (cave_feat[y][x] < FEAT_SECRET)
			{
				if (!in_bounds_fully(y, x)) continue;


				if (cave_feat[y][x] > FEAT_INVIS)
				{

					cave_info[y][x] |= (CAVE_MARK);
					light_spot(y, x);
				}


				for (i = 0; i < 8; i++)
				{
					int yy = y + ddy_ddd[i];
					int xx = x + ddx_ddd[i];


					if (cave_feat[yy][xx] >= FEAT_SECRET)
					{

						cave_info[yy][xx] |= (CAVE_MARK);
						light_spot(yy, xx);
					}
				}
			}
		}
	}
}
