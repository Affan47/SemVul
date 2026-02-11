cv_repeat_srch(EditLine *el, Int c)
{

#ifdef SDEBUG
	(void) fprintf(el->el_errfile, "dir %d patlen %d patbuf %s\n",
	    c, el->el_search.patlen, ct_encode_string(el->el_search.patbuf));
#endif

	el->el_state.lastcmd = (el_action_t) c;
	el->el_line.lastchar = el->el_line.buffer;

	switch (c) {
	case ED_SEARCH_NEXT_HISTORY:
		return ed_search_next_history(el, 0);
	case ED_SEARCH_PREV_HISTORY:
		return ed_search_prev_history(el, 0);
	default:
		return CC_ERROR;
	}
}
