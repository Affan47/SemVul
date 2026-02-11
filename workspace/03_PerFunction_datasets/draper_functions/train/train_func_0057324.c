diff_lnum_win(lnum, wp)
    linenr_T	lnum;
    win_T	*wp;
{
    diff_T	*dp;
    int		idx;
    int		i;
    linenr_T	n;

    idx = diff_buf_idx(curbuf);
    if (idx == DB_COUNT)
	return (linenr_T)0;

    if (curtab->tp_diff_invalid)
	ex_diffupdate(NULL);


    for (dp = curtab->tp_first_diff; dp != NULL; dp = dp->df_next)
	if (lnum <= dp->df_lnum[idx] + dp->df_count[idx])
	    break;


    if (dp == NULL)
	return wp->w_buffer->b_ml.ml_line_count
					- (curbuf->b_ml.ml_line_count - lnum);


    i = diff_buf_idx(wp->w_buffer);
    if (i == DB_COUNT)
	return (linenr_T)0;

    n = lnum + (dp->df_lnum[i] - dp->df_lnum[idx]);
    if (n > dp->df_lnum[i] + dp->df_count[i])
	n = dp->df_lnum[i] + dp->df_count[i];
    return n;
}
