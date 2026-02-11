diff_win_options(wp, addbuf)
    win_T	*wp;
    int		addbuf;
{
    wp->w_p_diff = TRUE;
    wp->w_p_scb = TRUE;
    wp->w_p_wrap = FALSE;
# ifdef FEAT_FOLDING
    {
	win_T	    *old_curwin = curwin;

	curwin = wp;
	curbuf = curwin->w_buffer;
	set_string_option_direct((char_u *)"fdm", -1, (char_u *)"diff",
						       OPT_LOCAL|OPT_FREE, 0);
	curwin = old_curwin;
	curbuf = curwin->w_buffer;
	wp->w_p_fdc = diff_foldcolumn;
	wp->w_p_fen = TRUE;
	wp->w_p_fdl = 0;
	foldUpdateAll(wp);

	changed_window_setting_win(wp);
    }
# endif
#ifdef FEAT_SCROLLBIND
    if (vim_strchr(p_sbo, 'h') == NULL)
	do_cmdline_cmd((char_u *)"set sbo+=hor");
#endif

    if (addbuf)
	diff_buf_add(wp->w_buffer);
    redraw_win_later(wp, NOT_VALID);
}
