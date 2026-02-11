make_windows(count)
	int		count;
{
	int		maxcount;
	int		todo;
	int		p_sb_save;


	maxcount = (curwin->w_height + curwin->w_status_height) /
											(MIN_ROWS + STATUS_HEIGHT);
	if (count > maxcount)
		count = maxcount;


	if ((p_ls == 2 || (count > 1 && p_ls == 1)) && curwin->w_status_height == 0)
	{
		curwin->w_status_height = STATUS_HEIGHT;
		curwin->w_height -= STATUS_HEIGHT;
	}


	p_sb_save = p_sb;
	p_sb = FALSE;

	for (todo = count - 1; todo > 0; --todo)
		if (win_split((long)(curwin->w_height - (curwin->w_height - todo
				* STATUS_HEIGHT) / (todo + 1) - STATUS_HEIGHT), FALSE) == FAIL)
			break;
	p_sb = p_sb_save;


	return (count - todo);
}
