op_shift(oap, curs_top, amount)
    oparg_T	    *oap;
    int		    curs_top;
    int		    amount;
{
    long	    i;
    int		    first_char;
    char_u	    *s;
#ifdef FEAT_VISUAL
    int		    block_col = 0;
#endif

    if (u_save((linenr_T)(oap->start.lnum - 1),
				       (linenr_T)(oap->end.lnum + 1)) == FAIL)
	return;

#ifdef FEAT_VISUAL
    if (oap->block_mode)
	block_col = curwin->w_cursor.col;
#endif

    for (i = oap->line_count; --i >= 0; )
    {
	first_char = *ml_get_curline();
	if (first_char == NUL)
	    curwin->w_cursor.col = 0;
#ifdef FEAT_VISUALEXTRA
	else if (oap->block_mode)
	    shift_block(oap, amount);
#endif
	else


#if defined(FEAT_SMARTINDENT) || defined(FEAT_CINDENT)
	    if (first_char != '#' || !preprocs_left())
#endif
	{
	    shift_line(oap->op_type == OP_LSHIFT, p_sr, amount, FALSE);
	}
	++curwin->w_cursor.lnum;
    }

    changed_lines(oap->start.lnum, 0, oap->end.lnum + 1, 0L);

#ifdef FEAT_VISUAL
    if (oap->block_mode)
    {
	curwin->w_cursor.lnum = oap->start.lnum;
	curwin->w_cursor.col = block_col;
    }
    else
#endif
	if (curs_top)
    {
	curwin->w_cursor.lnum = oap->start.lnum;
	beginline(BL_SOL | BL_FIX);
    }
    else
	--curwin->w_cursor.lnum;

    if (oap->line_count > p_report)
    {
	if (oap->op_type == OP_RSHIFT)
	    s = (char_u *)">";
	else
	    s = (char_u *)"<";
	if (oap->line_count == 1)
	{
	    if (amount == 1)
		sprintf((char *)IObuff, _("1 line %sed 1 time"), s);
	    else
		sprintf((char *)IObuff, _("1 line %sed %d times"), s, amount);
	}
	else
	{
	    if (amount == 1)
		sprintf((char *)IObuff, _("%ld lines %sed 1 time"),
							  oap->line_count, s);
	    else
		sprintf((char *)IObuff, _("%ld lines %sed %d times"),
						  oap->line_count, s, amount);
	}
	msg(IObuff);
    }


    curbuf->b_op_start = oap->start;
    curbuf->b_op_end.lnum = oap->end.lnum;
    curbuf->b_op_end.col = (colnr_T)STRLEN(ml_get(oap->end.lnum));
    if (curbuf->b_op_end.col > 0)
	--curbuf->b_op_end.col;
}
