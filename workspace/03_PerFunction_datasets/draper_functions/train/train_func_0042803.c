find_match_paren(ind_maxparen)
    int		ind_maxparen;
{
    pos_T	cursor_save;
    pos_T	*trypos;
    static pos_T pos_copy;

    cursor_save = curwin->w_cursor;
    if ((trypos = findmatchlimit(NULL, '(', 0, ind_maxparen)) != NULL)
    {

	if ((colnr_T)cin_skip2pos(trypos) > trypos->col)
	    trypos = NULL;
	else
	{
	    pos_copy = *trypos;
	    trypos = &pos_copy;
	    curwin->w_cursor = *trypos;
	    if (ind_find_start_comment() != NULL)
		trypos = NULL;
	}
    }
    curwin->w_cursor = cursor_save;
    return trypos;
}
