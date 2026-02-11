FScreenGetPrimaryScreen(XEvent *ev)
{
	if (!is_xinerama_enabled)
	{
		return 0;
	}
	if (primary_scr == FSCREEN_GLOBAL)
	{
		return 0;
	}
	else if (primary_scr == FSCREEN_CURRENT)
	{
		int mx;
		int my;


		GetMouseXY(ev, &mx, &my);
		return FindScreenOfXY(mx, my);
	}
	else if (primary_scr < 0 || primary_scr >= last_to_check)
	{

		return 0;
	}

	return primary_scr + 1;
}
