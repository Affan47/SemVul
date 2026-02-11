copy_loclist(from, to)
    win_T	*from;
    win_T	*to;
{
    qf_info_T	*qi;
    int		idx;
    int		i;


    if (IS_LL_WINDOW(from))
	qi = from->w_llist_ref;
    else
	qi = from->w_llist;

    if (qi == NULL)
	return;


    if ((to->w_llist = ll_new_list()) == NULL)
	return;

    to->w_llist->qf_listcount = qi->qf_listcount;


    for (idx = 0; idx < qi->qf_listcount; idx++)
    {
	qf_list_T   *from_qfl;
	qf_list_T   *to_qfl;

	to->w_llist->qf_curlist = idx;

	from_qfl = &qi->qf_lists[idx];
	to_qfl = &to->w_llist->qf_lists[idx];


	to_qfl->qf_nonevalid = from_qfl->qf_nonevalid;
	to_qfl->qf_count = 0;
	to_qfl->qf_index = 0;
	to_qfl->qf_start = NULL;
	to_qfl->qf_ptr = NULL;
	if (from_qfl->qf_title != NULL)
	    to_qfl->qf_title = vim_strsave(from_qfl->qf_title);
	else
	    to_qfl->qf_title = NULL;

	if (from_qfl->qf_count)
	{
	    qfline_T    *from_qfp;
	    qfline_T    *prevp = NULL;


	    for (i = 0, from_qfp = from_qfl->qf_start; i < from_qfl->qf_count;
		 ++i, from_qfp = from_qfp->qf_next)
	    {
		if (qf_add_entry(to->w_llist, &prevp,
				 NULL,
				 NULL,
				 0,
				 from_qfp->qf_text,
				 from_qfp->qf_lnum,
				 from_qfp->qf_col,
				 from_qfp->qf_viscol,
				 from_qfp->qf_pattern,
				 from_qfp->qf_nr,
				 0,
				 from_qfp->qf_valid) == FAIL)
		{
		    qf_free_all(to);
		    return;
		}


		prevp->qf_fnum = from_qfp->qf_fnum;
		prevp->qf_type = from_qfp->qf_type;
		if (from_qfl->qf_ptr == from_qfp)
		    to_qfl->qf_ptr = prevp;
	    }
	}

	to_qfl->qf_index = from_qfl->qf_index;


	if (to_qfl->qf_nonevalid == TRUE)
	    to_qfl->qf_ptr = to_qfl->qf_start;
    }

    to->w_llist->qf_curlist = qi->qf_curlist;
}
