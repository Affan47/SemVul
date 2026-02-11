updateScreen(type)
	int 			type;
{
	WIN				*wp;

	screenalloc(TRUE);
	if (Nextscreen == NULL)
		return;

	if (must_redraw)
	{
		if (type < must_redraw)
			type = must_redraw;
		must_redraw = 0;
	}

	if (type == CURSUPD)
	{
		curwin->w_lsize_valid = 0;
		cursupdate();
		return;
	}
	if (curwin->w_lsize_valid == 0 && type != CLEAR)
		type = NOT_VALID;

 	if (RedrawingDisabled)
	{
		must_redraw = type;
		return;
	}


	if (msg_scrolled)
	{
		clear_cmdline = TRUE;
		if (msg_scrolled > Rows - 5)
			type = CLEAR;
		else if (type != CLEAR)
		{
			if (screen_ins_lines(0, 0, msg_scrolled, (int)Rows) == FAIL)
				type = CLEAR;
			win_rest_invalid(firstwin);
		}
		msg_scrolled = 0;
	}


	compute_cmdrow();

	if (type == CLEAR)
	{
		screenclear();
		type = NOT_VALID;
	}

	if (clear_cmdline)
		gotocmdline(TRUE, NUL);


	if ((type == VALID && curwin->w_topline == curwin->w_lsize_lnum[0]) ||
			(type == INVERTED && old_cursor.lnum == curwin->w_cursor.lnum &&
					old_cursor.col == curwin->w_cursor.col && curwin->w_curswant == oldCurswant))
		return;

	curwin->w_redr_type = type;


	cursor_off();
	for (wp = firstwin; wp; wp = wp->w_next)
	{
		if (wp->w_redr_type)
			win_update(wp);
		if (wp->w_redr_status)
			win_redr_status(wp);
	}
	if (redraw_cmdline)
		showmode();
}
