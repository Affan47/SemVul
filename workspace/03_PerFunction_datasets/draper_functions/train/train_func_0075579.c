ed_prev_history(EditLine *el, Int c __attribute__((__unused__)))
{
	char beep = 0;
	int sv_event = el->el_history.eventno;

	el->el_chared.c_undo.len = -1;
	*el->el_line.lastchar = '\0';

	if (el->el_history.eventno == 0) {

		(void) Strncpy(el->el_history.buf, el->el_line.buffer,
		    EL_BUFSIZ);
		el->el_history.last = el->el_history.buf +
		    (el->el_line.lastchar - el->el_line.buffer);
	}
	el->el_history.eventno += el->el_state.argument;

	if (hist_get(el) == CC_ERROR) {
		if (el->el_map.type == MAP_VI) {
			el->el_history.eventno = sv_event;

		}
		beep = 1;

		(void) hist_get(el);
	}
	if (beep)
		return CC_REFRESH_BEEP;
	return CC_REFRESH;
}
