_nc_mvcur_resume(void)

{

    if (enter_ca_mode) {
	TPUTS_TRACE("enter_ca_mode");
	putp(enter_ca_mode);
    }


    reset_scroll_region();
    SP->_cursrow = SP->_curscol = -1;


    if (SP->_cursor != -1) {
	int cursor = SP->_cursor;
	SP->_cursor = -1;
	curs_set(cursor);
    }
}
