_nc_curs_set(SCREEN *sp, int vis)
{
    int result = ERR;

    T((T_CALLED("curs_set(%d)"), vis));
    if (sp != 0 && vis >= 0 && vis <= 2) {
	int cursor = sp->_cursor;

	if (vis == cursor) {
	    result = cursor;
	} else {
	    switch (vis) {
	    case 2:
		result = _nc_putp_flush("cursor_visible", cursor_visible);
		break;
	    case 1:
		result = _nc_putp_flush("cursor_normal", cursor_normal);
		break;
	    case 0:
		result = _nc_putp_flush("cursor_invisible", cursor_invisible);
		break;
	    }
	    if (result != ERR)
		result = (cursor == -1 ? 1 : cursor);
	    sp->_cursor = vis;
	}
    }
    returnCode(result);
}
