target_set_location(int y, int x)
{

	if (in_bounds_fully(y, x))
	{

		target_set = TRUE;
		target_who = 0;
		target_y = y;
		target_x = x;
	}


	else
	{

		target_set = FALSE;
		target_who = 0;
		target_y = 0;
		target_x = 0;
	}
}
