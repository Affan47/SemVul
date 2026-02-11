_nc_screen_wrap(void)
{
    UpdateAttrs(normal);
#if NCURSES_EXT_FUNCS
    if (SP->_coloron
	&& !SP->_default_color) {
	static const NCURSES_CH_T blank = NewChar(BLANK_TEXT);
	SP->_default_color = TRUE;
	_nc_do_color(-1, 0, FALSE, _nc_outch);
	SP->_default_color = FALSE;

	mvcur(SP->_cursrow, SP->_curscol, screen_lines - 1, 0);

	ClrToEOL(blank, TRUE);
    }
#endif
    if (SP->_color_defs) {
	_nc_reset_colors();
    }
}
