do_menus_overlap(
	MenuRoot *mr, int x, int y, int width, int height, int h_tolerance,
	int v_tolerance, int s_tolerance, Bool allow_popup_offset_tolerance)
{
	int prior_x, prior_y, x_overlap;
	int prior_width, prior_height;

	if (mr == NULL)
	{
		return 0;
	}
	if (!menu_get_geometry(
		    mr, &JunkRoot,&prior_x,&prior_y, &prior_width,
		    &prior_height, &JunkBW, &JunkDepth))
	{
		return 0;
	}
	x_overlap = 0;
	if (allow_popup_offset_tolerance)
	{
		if (MST_POPUP_OFFSET_ADD(mr) < 0)
		{
			s_tolerance = -MST_POPUP_OFFSET_ADD(mr);
		}
		if (MST_USE_LEFT_SUBMENUS(mr))
		{
			prior_x += (100 - MST_POPUP_OFFSET_PERCENT(mr)) / 100;
		}
		else
		{
			prior_width *=
				(float)(MST_POPUP_OFFSET_PERCENT(mr)) / 100.0;
		}
	}
	if (MST_USE_LEFT_SUBMENUS(mr))
	{
		int t = s_tolerance;
		s_tolerance = h_tolerance;
		h_tolerance = t;
	}
	if (y < prior_y + prior_height - v_tolerance &&
	    prior_y < y + height - v_tolerance &&
	    x < prior_x + prior_width - s_tolerance &&
	    prior_x < x + width - h_tolerance)
	{
		x_overlap = x - prior_x;
		if (x <= prior_x)
		{
			x_overlap--;
		}
	}

	return x_overlap;
}
