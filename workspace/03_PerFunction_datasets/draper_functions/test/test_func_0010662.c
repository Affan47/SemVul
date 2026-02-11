foldCheckClose()
{
    if (*p_fcl != NUL)
    {
	checkupdate(curwin);
	if (checkCloseRec(&curwin->w_folds, curwin->w_cursor.lnum,
							(int)curwin->w_p_fdl))
	    changed_window_setting();
    }
}
