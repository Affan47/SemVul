screen_char (zchar c)
{
	if (gos_linepending && (gos_curwin == gos_linewin))
	{
		gos_cancel_pending_line();
		if (gos_curwin == gos_upper)
		{
			curx = 1;
			cury ++;
		}
		if (c == '\n')
			return;
	}


	int forcefix = ((h_flags & FIXED_FONT_FLAG) != 0);
	int curfix = ((curstyle & FIXED_WIDTH_STYLE) != 0);
	if (forcefix && !curfix)
	{
		zargs[0] = 0xf000;
		z_set_text_style();
		fixforced = TRUE;
	}
	else if (!forcefix && fixforced)
	{
		zargs[0] = 0xf000;
		z_set_text_style();
		fixforced = FALSE;
	}

	if (gos_upper && gos_curwin == gos_upper)
	{
		if (c == '\n' || c == ZC_RETURN) {
			glk_put_char('\n');
			curx = 1;
			cury ++;
		}
		else {
			if (cury == 1)
			{
				if (curx <= ((sizeof statusline / sizeof(zchar)) - 1))
				{
					statusline[curx - 1] = c;
					statusline[curx] = 0;
				}
				if (curx < h_screen_cols)
				{
					glk_put_char_uni(c);
				}
				else if (curx == h_screen_cols)
				{
					glk_put_char_uni(c);
					glk_window_move_cursor(gos_curwin, curx-1, cury-1);
				}
				else
				{
					smartstatusline();
				}
				curx ++;
			}
			else
			{
				if (curx < h_screen_cols)
				{
					glk_put_char_uni(c);
				}
				else if (curx == (h_screen_cols))
				{
					glk_put_char_uni(c);
					glk_window_move_cursor(gos_curwin, curx-1, cury-1);
				}
				curx++;
			}
		}
	}
	else if (gos_curwin == gos_lower)
	{
		if (c == ZC_RETURN)
			glk_put_char('\n');
		else glk_put_char_uni(c);
	}
}
