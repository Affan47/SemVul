count_feats(int *y, int *x, bool (*test)(int feat), bool under)
{
	int d;
	int xx, yy;
	int count = 0;


	for (d = 0; d < 9; d++)
	{

		if ((d == 8) && !under) continue;


		yy = p_ptr->py + ddy_ddd[d];
		xx = p_ptr->px + ddx_ddd[d];


		if (!in_bounds_fully(yy, xx)) continue;


		if (!(cave_info[yy][xx] & (CAVE_MARK))) continue;


		if (!((*test)(cave_feat[yy][xx]))) continue;


		++count;


		*y = yy;
		*x = xx;
	}


	return count;
}
