ed_next_history(EditLine *el, Int c __attribute__((__unused__)))
{
	el_action_t beep = CC_REFRESH, rval;

	el->el_chared.c_undo.len = -1;
	*el->el_line.lastchar = '\0';

	el->el_history.eventno -= el->el_state.argument;

	if (el->el_history.eventno < 0) {
		el->el_history.eventno = 0;
		beep = CC_REFRESH_BEEP;
	}
	rval = hist_get(el);
	if (rval == CC_REFRESH)
		return beep;
	return rval;

}
