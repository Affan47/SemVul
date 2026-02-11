getvcol(wp, pos, start, cursor, end)
    win_T	*wp;
    pos_T	*pos;
    colnr_T	*start;
    colnr_T	*cursor;
    colnr_T	*end;
{
    colnr_T	vcol;
    char_u	*ptr;
    char_u	*posptr;
    int		incr;
    int		head;
    int		ts = wp->w_buffer->b_p_ts;
    int		c;

    vcol = 0;
    ptr = ml_get_buf(wp->w_buffer, pos->lnum, FALSE);
    if (pos->col == MAXCOL)
	posptr = NULL;
    else
	posptr = ptr + pos->col;


    if ((!wp->w_p_list || lcs_tab1 != NUL)
#ifdef FEAT_LINEBREAK
	    && !wp->w_p_lbr && *p_sbr == NUL
#endif
       )
    {
#ifndef FEAT_MBYTE
	head = 0;
#endif
	for (;;)
	{
#ifdef FEAT_MBYTE
	    head = 0;
#endif
	    c = *ptr;

	    if (c == NUL)
	    {
		incr = 1;
		break;
	    }

	    if (c == TAB)
		incr = ts - (vcol % ts);
	    else
	    {
#ifdef FEAT_MBYTE
		if (has_mbyte)
		{


		    if (enc_utf8 && c >= 0x80)
			incr = utf_ptr2cells(ptr);
		    else
			incr = CHARSIZE(c);


		    if (incr == 2 && wp->w_p_wrap && MB_BYTE2LEN(*ptr) > 1
			    && in_win_border(wp, vcol))
		    {
			++incr;
			head = 1;
		    }
		}
		else
#endif
		    incr = CHARSIZE(c);
	    }

	    if (posptr != NULL && ptr >= posptr)
		break;

	    vcol += incr;
	    mb_ptr_adv(ptr);
	}
    }
    else
    {
	for (;;)
	{

	    head = 0;
	    incr = win_lbr_chartabsize(wp, ptr, vcol, &head);

	    if (*ptr == NUL)
	    {
		incr = 1;
		break;
	    }

	    if (posptr != NULL && ptr >= posptr)
		break;

	    vcol += incr;
	    mb_ptr_adv(ptr);
	}
    }
    if (start != NULL)
	*start = vcol + head;
    if (end != NULL)
	*end = vcol + incr - 1;
    if (cursor != NULL)
    {
	if (*ptr == TAB
		&& (State & NORMAL)
		&& !wp->w_p_list
		&& !virtual_active()
#ifdef FEAT_VISUAL
		&& !(VIsual_active
				   && (*p_sel == 'e' || ltoreq(*pos, VIsual)))
#endif
		)
	    *cursor = vcol + incr - 1;
	else
	    *cursor = vcol + head;
    }
}
