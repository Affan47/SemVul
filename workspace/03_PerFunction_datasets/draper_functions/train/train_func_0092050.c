wchgat(WINDOW *win, int n, attr_t attr, short color, const void *opts GCC_UNUSED)
{
    int i;

    T((T_CALLED("wchgat(%p,%d,%s,%d)"), win, n, _traceattr(attr), color));

    if (win) {
	struct ldat *line = &(win->_line[win->_cury]);

	toggle_attr_on(attr, COLOR_PAIR(color));

	for (i = win->_curx; i <= win->_maxx && (n == -1 || (n-- > 0)); i++) {
	    SetAttr(line->text[i], attr);
	    SetPair(line->text[i], color);
	    CHANGED_CELL(line, i);
	}

	returnCode(OK);
    } else
	returnCode(ERR);
}
