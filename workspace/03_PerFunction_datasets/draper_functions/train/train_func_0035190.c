diff_check_unchanged(tp, dp)
    tabpage_T	*tp;
    diff_T	*dp;
{
    int		i_org;
    int		i_new;
    int		off_org, off_new;
    char_u	*line_org;
    int		dir = FORWARD;


    for (i_org = 0; i_org < DB_COUNT; ++i_org)
	if (tp->tp_diffbuf[i_org] != NULL)
	    break;
    if (i_org == DB_COUNT)
	return;

    if (diff_check_sanity(tp, dp) == FAIL)
	return;


    off_org = 0;
    off_new = 0;
    for (;;)
    {


	while (dp->df_count[i_org] > 0)
	{

	    if (dir == BACKWARD)
		off_org = dp->df_count[i_org] - 1;
	    line_org = vim_strsave(ml_get_buf(tp->tp_diffbuf[i_org],
					dp->df_lnum[i_org] + off_org, FALSE));
	    if (line_org == NULL)
		return;
	    for (i_new = i_org + 1; i_new < DB_COUNT; ++i_new)
	    {
		if (tp->tp_diffbuf[i_new] == NULL)
		    continue;
		if (dir == BACKWARD)
		    off_new = dp->df_count[i_new] - 1;

		if (off_new < 0 || off_new >= dp->df_count[i_new])
		    break;
		if (diff_cmp(line_org, ml_get_buf(tp->tp_diffbuf[i_new],
				   dp->df_lnum[i_new] + off_new, FALSE)) != 0)
		    break;
	    }
	    vim_free(line_org);


	    if (i_new != DB_COUNT)
		break;


	    for (i_new = i_org; i_new < DB_COUNT; ++i_new)
		if (tp->tp_diffbuf[i_new] != NULL)
		{
		    if (dir == FORWARD)
			++dp->df_lnum[i_new];
		    --dp->df_count[i_new];
		}
	}
	if (dir == BACKWARD)
	    break;
	dir = BACKWARD;
    }
}
