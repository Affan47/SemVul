checkpcmark()
{
	if (curwin->w_prev_pcmark.lnum != 0 &&
			(curwin->w_pcmark.lnum == curwin->w_cursor.lnum ||
			curwin->w_pcmark.lnum == 0))
	{
		curwin->w_pcmark = curwin->w_prev_pcmark;
		curwin->w_prev_pcmark.lnum = 0;
	}
}
