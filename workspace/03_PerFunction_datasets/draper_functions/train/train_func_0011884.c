make_windows(count, vertical)
    int		count;
    int		vertical UNUSED;
{
    int		maxcount;
    int		todo;

#ifdef FEAT_VERTSPLIT
    if (vertical)
    {


	maxcount = (curwin->w_width + curwin->w_vsep_width
					     - (p_wiw - p_wmw)) / (p_wmw + 1);
    }
    else
#endif
    {

	maxcount = (curwin->w_height + curwin->w_status_height
				  - (p_wh - p_wmh)) / (p_wmh + STATUS_HEIGHT);
    }

    if (maxcount < 2)
	maxcount = 2;
    if (count > maxcount)
	count = maxcount;


    if (count > 1)
	last_status(TRUE);

#ifdef FEAT_AUTOCMD


    block_autocmds();
#endif


    for (todo = count - 1; todo > 0; --todo)
#ifdef FEAT_VERTSPLIT
	if (vertical)
	{
	    if (win_split(curwin->w_width - (curwin->w_width - todo)
			/ (todo + 1) - 1, WSP_VERT | WSP_ABOVE) == FAIL)
		break;
	}
	else
#endif
	{
	    if (win_split(curwin->w_height - (curwin->w_height - todo
			    * STATUS_HEIGHT) / (todo + 1)
			- STATUS_HEIGHT, WSP_ABOVE) == FAIL)
		break;
	}

#ifdef FEAT_AUTOCMD
    unblock_autocmds();
#endif


    return (count - todo);
}
