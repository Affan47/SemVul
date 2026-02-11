get_beval_info(beval, getword, winp, lnump, textp, colp)
    BalloonEval	*beval;
    int		getword;
    win_T	**winp;
    linenr_T	*lnump;
    char_u	**textp;
    int		*colp;
{
    win_T	*wp;
    int		row, col;
    char_u	*lbuf;
    linenr_T	lnum;

    *textp = NULL;
    row = Y_2_ROW(beval->y);
    col = X_2_COL(beval->x);
#ifdef FEAT_WINDOWS
    wp = mouse_find_win(&row, &col);
#else
    wp = firstwin;
#endif
    if (wp != NULL && row < wp->w_height && col < W_WIDTH(wp))
    {


	if (!mouse_comp_pos(wp, &row, &col, &lnum))
	{

	    lbuf = ml_get_buf(wp->w_buffer, lnum, FALSE);
	    if (col <= win_linetabsize(wp, lbuf, (colnr_T)MAXCOL))
	    {

		if (getword)
		{


		    int		len;
		    pos_T	*spos = NULL, *epos = NULL;

		    if (VIsual_active)
		    {
			if (lt(VIsual, curwin->w_cursor))
			{
			    spos = &VIsual;
			    epos = &curwin->w_cursor;
			}
			else
			{
			    spos = &curwin->w_cursor;
			    epos = &VIsual;
			}
		    }

		    col = vcol2col(wp, lnum, col);

		    if (VIsual_active
			    && wp->w_buffer == curwin->w_buffer
			    && (lnum == spos->lnum
				? col >= (int)spos->col
				: lnum > spos->lnum)
			    && (lnum == epos->lnum
				? col <= (int)epos->col
				: lnum < epos->lnum))
		    {


			if (spos->lnum != epos->lnum || spos->col == epos->col)
			    return FAIL;

			lbuf = ml_get_buf(curwin->w_buffer, VIsual.lnum, FALSE);
			len = epos->col - spos->col;
			if (*p_sel != 'e')
			    len += MB_PTR2LEN(lbuf + epos->col);
			lbuf = vim_strnsave(lbuf + spos->col, len);
			lnum = spos->lnum;
			col = spos->col;
		    }
		    else
		    {

			++emsg_off;
			len = find_ident_at_pos(wp, lnum, (colnr_T)col, &lbuf,
					FIND_IDENT + FIND_STRING + FIND_EVAL);
			--emsg_off;
			if (len == 0)
			    return FAIL;
			lbuf = vim_strnsave(lbuf, len);
		    }
		}

		*winp = wp;
		*lnump = lnum;
		*textp = lbuf;
		*colp = col;
		beval->ts = wp->w_buffer->b_p_ts;
		return OK;
	    }
	}
    }

    return FAIL;
}
