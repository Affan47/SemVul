blit_medals()
{
	int idx;

	for (idx=0; idx<Num_medals; idx++) {
		if (Player_score->medals[idx] > 0) {
			gr_set_bitmap(Medal_bitmaps[idx]);
			gr_bitmap(Medal_coords[gr_screen.res][idx][0], Medal_coords[gr_screen.res][idx][1]);
		}
	}


	gr_set_bitmap(Rank_bm);
	gr_bitmap(Medal_coords[gr_screen.res][RANK_MEDAL_REGION][0], Medal_coords[gr_screen.res][RANK_MEDAL_REGION][1]);
}
