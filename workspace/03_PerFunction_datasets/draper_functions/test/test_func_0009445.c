stick_across_pages(F_CMD_ARGS, int toggle)
{
	FvwmWindow *fw = exc->w.fw;

	if ((toggle == 1 && IS_STICKY_ACROSS_PAGES(fw)) ||
	    (toggle == 0 && !IS_STICKY_ACROSS_PAGES(fw)))
	{
		return 0;
	}
	if (IS_STICKY_ACROSS_PAGES(fw))
	{
		SET_STICKY_ACROSS_PAGES(fw, 0);
	}
	else
	{
		if (!IsRectangleOnThisPage(&fw->g.frame, Scr.CurrentDesk))
		{
			action = "";
			__move_window(F_PASS_ARGS, False, MOVE_PAGE);
		}
		SET_STICKY_ACROSS_PAGES(fw, 1);
	}

	return 1;
}
