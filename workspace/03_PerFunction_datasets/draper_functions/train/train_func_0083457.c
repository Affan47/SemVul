stars_load_first_valid_background()
{
	int background_idx = stars_get_first_valid_background();

#ifndef NDEBUG
	if (background_idx < 0 && !Fred_running)
	{
		int i;
		bool at_least_one_bitmap = false;
		for (i = 0; i < Num_backgrounds; i++)
		{
			if (Backgrounds[i].bitmaps.size() > 0)
				at_least_one_bitmap = true;
		}

		if (at_least_one_bitmap)
		{
			if (Num_backgrounds == 1)
				Warning(LOCATION, "Unable to find a sufficient number of bitmaps for this mission's background.  The background will not be displayed.");
			else if (Num_backgrounds > 1)
				Warning(LOCATION, "Unable to find a sufficient number of bitmaps for any background listed in this mission.  No background will be displayed.");
		}
	}
#endif

	stars_load_background(background_idx);
}
