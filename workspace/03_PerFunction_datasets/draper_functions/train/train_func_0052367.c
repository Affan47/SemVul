vi_end_word(EditLine *el, Int c __attribute__((__unused__)))
{

	if (el->el_line.cursor == el->el_line.lastchar)
		return CC_ERROR;

	el->el_line.cursor = cv__endword(el->el_line.cursor,
	    el->el_line.lastchar, el->el_state.argument, cv__isword);

	if (el->el_chared.c_vcmd.action != NOP) {
		el->el_line.cursor++;
		cv_delfini(el);
		return CC_REFRESH;
	}
	return CC_CURSOR;
}
