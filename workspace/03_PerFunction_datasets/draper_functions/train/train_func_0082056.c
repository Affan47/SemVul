n_start_visual_mode(c)
    int		c;
{
#ifdef FEAT_CONCEAL

    conceal_check_cursur_line();
#endif

    VIsual_mode = c;
    VIsual_active = TRUE;
    VIsual_reselect = TRUE;
#ifdef FEAT_VIRTUALEDIT


    if (c == Ctrl_V && (ve_flags & VE_BLOCK) && gchar_cursor() == TAB)
    {
	validate_virtcol();
	coladvance(curwin->w_virtcol);
    }
#endif
    VIsual = curwin->w_cursor;

#ifdef FEAT_FOLDING
    foldAdjustVisual();
#endif

#ifdef FEAT_MOUSE
    setmouse();
#endif
#ifdef FEAT_CONCEAL

    conceal_check_cursur_line();
#endif

    if (p_smd && msg_silent == 0)
	redraw_cmdline = TRUE;
#ifdef FEAT_CLIPBOARD


    clip_star.vmode = NUL;
#endif


    if (curwin->w_redr_type < INVERTED)
    {
	curwin->w_old_cursor_lnum = curwin->w_cursor.lnum;
	curwin->w_old_visual_lnum = curwin->w_cursor.lnum;
    }
}
