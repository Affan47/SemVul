waddnstr(WINDOW *win, const char *astr, int n)
{
    const char *str = astr;
    int code = ERR;

    T((T_CALLED("waddnstr(%p,%s,%d)"), win, _nc_visbufn(astr, n), n));

    if (win && (str != 0)) {
	TR(TRACE_VIRTPUT | TRACE_ATTRS,
	   ("... current %s", _traceattr(WINDOW_ATTRS(win))));
	code = OK;
	if (n < 0)
	    n = (int) strlen(astr);

	TR(TRACE_VIRTPUT, ("str is not null, length = %d", n));
	while ((n-- > 0) && (*str != '\0')) {
	    NCURSES_CH_T ch;
	    TR(TRACE_VIRTPUT, ("*str = %#o", UChar(*str)));
	    SetChar(ch, UChar(*str++), A_NORMAL);
	    if (_nc_waddch_nosync(win, ch) == ERR) {
		code = ERR;
		break;
	    }
	}
	_nc_synchook(win);
    }
    TR(TRACE_VIRTPUT, ("waddnstr returns %d", code));
    returnCode(code);
}
