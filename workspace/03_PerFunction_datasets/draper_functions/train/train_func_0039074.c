diff_check(wp, lnum)
    win_T	*wp;
    linenr_T	lnum;
{
    int		idx;
    diff_T	*dp;
    int		maxcount;
    int		i;
    buf_T	*buf = wp->w_buffer;
    int		cmp;

    if (curtab->tp_diff_invalid)
	ex_diffupdate(NULL);

    if (curtab->tp_first_diff == NULL || !wp->w_p_diff)
	return 0;


    if (lnum < 1 || lnum > buf->b_ml.ml_line_count + 1)
	return 0;

    idx = diff_buf_idx(buf);
    if (idx == DB_COUNT)
	return 0;

#ifdef FEAT_FOLDING

    if (hasFoldingWin(wp, lnum, NULL, NULL, TRUE, NULL))
	return 0;
#endif


    for (dp = curtab->tp_first_diff; dp != NULL; dp = dp->df_next)
	if (lnum <= dp->df_lnum[idx] + dp->df_count[idx])
	    break;
    if (dp == NULL || lnum < dp->df_lnum[idx])
	return 0;

    if (lnum < dp->df_lnum[idx] + dp->df_count[idx])
    {
	int	zero = FALSE;


	cmp = FALSE;
	for (i = 0; i < DB_COUNT; ++i)
	    if (i != idx && curtab->tp_diffbuf[i] != NULL)
	    {
		if (dp->df_count[i] == 0)
		    zero = TRUE;
		else
		{
		    if (dp->df_count[i] != dp->df_count[idx])
			return -1;
		    cmp = TRUE;
		}
	    }
	if (cmp)
	{


	    for (i = 0; i < DB_COUNT; ++i)
		if (i != idx && curtab->tp_diffbuf[i] != NULL && dp->df_count[i] != 0)
		    if (!diff_equal_entry(dp, idx, i))
			return -1;
	}


	if (zero == FALSE)
	    return 0;
	return -2;
    }


    if (!(diff_flags & DIFF_FILLER))
	return 0;


    maxcount = 0;
    for (i = 0; i < DB_COUNT; ++i)
	if (curtab->tp_diffbuf[i] != NULL && dp->df_count[i] > maxcount)
	    maxcount = dp->df_count[i];
    return maxcount - dp->df_count[idx];
}
