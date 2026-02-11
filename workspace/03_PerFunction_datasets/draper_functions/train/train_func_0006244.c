adjust_cursor_eol()
{
    if (curwin->w_cursor.col > 0
	    && gchar_cursor() == NUL
#ifdef FEAT_VIRTUALEDIT
	    && (ve_flags & VE_ONEMORE) == 0
#endif
	    && !(restart_edit || (State & INSERT)))
    {

	dec_cursor();

#ifdef FEAT_VIRTUALEDIT
	if (ve_flags == VE_ALL)
	{
	    colnr_T	    scol, ecol;


	    getvcol(curwin, &curwin->w_cursor, &scol, NULL, &ecol);
	    curwin->w_cursor.coladd = ecol - scol + 1;
	}
#endif
    }
}
