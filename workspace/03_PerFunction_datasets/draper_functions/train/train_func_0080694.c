ins_right()
{
#ifdef FEAT_FOLDING
    if ((fdo_flags & FDO_HOR) && KeyTyped)
	foldOpenCursor();
#endif
    undisplay_dollar();
    if (gchar_cursor() != NUL || virtual_active()
	    )
    {
	start_arrow(&curwin->w_cursor);
	curwin->w_set_curswant = TRUE;
#ifdef FEAT_VIRTUALEDIT
	if (virtual_active())
	    oneright();
	else
#endif
	{
#ifdef FEAT_MBYTE
	    if (has_mbyte)
		curwin->w_cursor.col += (*mb_ptr2len)(ml_get_cursor());
	    else
#endif
		++curwin->w_cursor.col;
	}

#ifdef FEAT_RIGHTLEFT
	revins_legal++;
	if (revins_chars)
	    revins_chars--;
#endif
    }


    else if (vim_strchr(p_ww, ']') != NULL
	    && curwin->w_cursor.lnum < curbuf->b_ml.ml_line_count)
    {
	start_arrow(&curwin->w_cursor);
	curwin->w_set_curswant = TRUE;
	++curwin->w_cursor.lnum;
	curwin->w_cursor.col = 0;
    }
    else
	vim_beep();
}
