ex_align(eap)
    exarg_T	*eap;
{
    pos_T	save_curpos;
    int		len;
    int		indent = 0;
    int		new_indent;
    int		has_tab;
    int		width;

#ifdef FEAT_RIGHTLEFT
    if (curwin->w_p_rl)
    {

	if (eap->cmdidx == CMD_right)
	    eap->cmdidx = CMD_left;
	else if (eap->cmdidx == CMD_left)
	    eap->cmdidx = CMD_right;
    }
#endif

    width = atoi((char *)eap->arg);
    save_curpos = curwin->w_cursor;
    if (eap->cmdidx == CMD_left)
    {
	if (width >= 0)
	    indent = width;
    }
    else
    {


	if (width <= 0)
	    width = curbuf->b_p_tw;
	if (width == 0 && curbuf->b_p_wm > 0)
	    width = W_WIDTH(curwin) - curbuf->b_p_wm;
	if (width <= 0)
	    width = 80;
    }

    if (u_save((linenr_T)(eap->line1 - 1), (linenr_T)(eap->line2 + 1)) == FAIL)
	return;

    for (curwin->w_cursor.lnum = eap->line1;
		 curwin->w_cursor.lnum <= eap->line2; ++curwin->w_cursor.lnum)
    {
	if (eap->cmdidx == CMD_left)
	    new_indent = indent;
	else
	{
	    has_tab = FALSE;
	    len = linelen(eap->cmdidx == CMD_right ? &has_tab
						   : NULL) - get_indent();

	    if (len <= 0)
		continue;

	    if (eap->cmdidx == CMD_center)
		new_indent = (width - len) / 2;
	    else
	    {
		new_indent = width - len;


		if (has_tab)
		    while (new_indent > 0)
		    {
			(void)set_indent(new_indent, 0);
			if (linelen(NULL) <= width)
			{


			    do
				(void)set_indent(++new_indent, 0);
			    while (linelen(NULL) <= width);
			    --new_indent;
			    break;
			}
			--new_indent;
		    }
	    }
	}
	if (new_indent < 0)
	    new_indent = 0;
	(void)set_indent(new_indent, 0);
    }
    changed_lines(eap->line1, 0, eap->line2 + 1, 0L);
    curwin->w_cursor = save_curpos;
    beginline(BL_WHITE | BL_FIX);
}
