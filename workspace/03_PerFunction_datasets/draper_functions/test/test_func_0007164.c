redrawWinline(lnum, invalid)
    linenr_T	lnum;
    int		invalid UNUSED;
{
#ifdef FEAT_FOLDING
    int		i;
#endif

    if (curwin->w_redraw_top == 0 || curwin->w_redraw_top > lnum)
	curwin->w_redraw_top = lnum;
    if (curwin->w_redraw_bot == 0 || curwin->w_redraw_bot < lnum)
	curwin->w_redraw_bot = lnum;
    redraw_later(VALID);

#ifdef FEAT_FOLDING
    if (invalid)
    {

	i = find_wl_entry(curwin, lnum);
	if (i >= 0)
	    curwin->w_lines[i].wl_valid = FALSE;
    }
#endif
}
