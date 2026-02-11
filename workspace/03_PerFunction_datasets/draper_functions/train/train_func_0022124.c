search_cmn(argvars, match_pos, flagsp)
    typval_T	*argvars;
    pos_T	*match_pos;
    int		*flagsp;
{
    int		flags;
    char_u	*pat;
    pos_T	pos;
    pos_T	save_cursor;
    int		save_p_ws = p_ws;
    int		dir;
    int		retval = 0;
    long	lnum_stop = 0;
    proftime_T	tm;
#ifdef FEAT_RELTIME
    long	time_limit = 0;
#endif
    int		options = SEARCH_KEEP;
    int		subpatnum;

    pat = get_tv_string(&argvars[0]);
    dir = get_search_arg(&argvars[1], flagsp);
    if (dir == 0)
	goto theend;
    flags = *flagsp;
    if (flags & SP_START)
	options |= SEARCH_START;
    if (flags & SP_END)
	options |= SEARCH_END;


    if (argvars[1].v_type != VAR_UNKNOWN && argvars[2].v_type != VAR_UNKNOWN)
    {
	lnum_stop = get_tv_number_chk(&argvars[2], NULL);
	if (lnum_stop < 0)
	    goto theend;
#ifdef FEAT_RELTIME
	if (argvars[3].v_type != VAR_UNKNOWN)
	{
	    time_limit = get_tv_number_chk(&argvars[3], NULL);
	    if (time_limit < 0)
		goto theend;
	}
#endif
    }

#ifdef FEAT_RELTIME

    profile_setlimit(time_limit, &tm);
#endif


    if (((flags & (SP_REPEAT | SP_RETCOUNT)) != 0)
	    || ((flags & SP_NOMOVE) && (flags & SP_SETPCMARK)))
    {
	EMSG2(_(e_invarg2), get_tv_string(&argvars[1]));
	goto theend;
    }

    pos = save_cursor = curwin->w_cursor;
    subpatnum = searchit(curwin, curbuf, &pos, dir, pat, 1L,
				options, RE_SEARCH, (linenr_T)lnum_stop, &tm);
    if (subpatnum != FAIL)
    {
	if (flags & SP_SUBPAT)
	    retval = subpatnum;
	else
	    retval = pos.lnum;
	if (flags & SP_SETPCMARK)
	    setpcmark();
	curwin->w_cursor = pos;
	if (match_pos != NULL)
	{

	    match_pos->lnum = pos.lnum;
	    match_pos->col = pos.col + 1;
	}


	check_cursor();
    }


    if (flags & SP_NOMOVE)
	curwin->w_cursor = save_cursor;
    else
	curwin->w_set_curswant = TRUE;
theend:
    p_ws = save_p_ws;

    return retval;
}
