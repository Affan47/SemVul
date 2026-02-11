findpar(pincl, dir, count, what, both)
    int		*pincl;
    int		dir;
    long	count;
    int		what;
    int		both;
{
    linenr_T	curr;
    int		did_skip;
    int		first;
    int		posix = (vim_strchr(p_cpo, CPO_PARA) != NULL);
#ifdef FEAT_FOLDING
    linenr_T	fold_first;
    linenr_T	fold_last;
    int		fold_skipped;

#endif

    curr = curwin->w_cursor.lnum;

    while (count--)
    {
	did_skip = FALSE;
	for (first = TRUE; ; first = FALSE)
	{
	    if (*ml_get(curr) != NUL)
		did_skip = TRUE;

#ifdef FEAT_FOLDING

	    fold_skipped = FALSE;
	    if (first && hasFolding(curr, &fold_first, &fold_last))
	    {
		curr = ((dir > 0) ? fold_last : fold_first) + dir;
		fold_skipped = TRUE;
	    }
#endif


	    if (!first && did_skip && (startPS(curr, what, both)
			   || (posix && what == NUL && *ml_get(curr) == '{')))
		break;

#ifdef FEAT_FOLDING
	    if (fold_skipped)
		curr -= dir;
#endif
	    if ((curr += dir) < 1 || curr > curbuf->b_ml.ml_line_count)
	    {
		if (count)
		    return FALSE;
		curr -= dir;
		break;
	    }
	}
    }
    setpcmark();
    if (both && *ml_get(curr) == '}')
	++curr;
    curwin->w_cursor.lnum = curr;
    if (curr == curbuf->b_ml.ml_line_count && what != '}')
    {
	if ((curwin->w_cursor.col = (colnr_T)STRLEN(ml_get(curr))) != 0)
	{
	    --curwin->w_cursor.col;
	    *pincl = TRUE;
	}
    }
    else
	curwin->w_cursor.col = 0;
    return TRUE;
}
