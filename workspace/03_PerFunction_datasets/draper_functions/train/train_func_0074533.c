ed_insert(EditLine *el, Int c)
{
	int count = el->el_state.argument;

	if (c == '\0')
		return CC_ERROR;

	if (el->el_line.lastchar + el->el_state.argument >=
	    el->el_line.limit) {

		if (!ch_enlargebufs(el, (size_t) count))
			return CC_ERROR;
	}

	if (count == 1) {
		if (el->el_state.inputmode == MODE_INSERT
		    || el->el_line.cursor >= el->el_line.lastchar)
			c_insert(el, 1);

		*el->el_line.cursor++ = c;
		re_fastaddc(el);
	} else {
		if (el->el_state.inputmode != MODE_REPLACE_1)
			c_insert(el, el->el_state.argument);

		while (count-- && el->el_line.cursor < el->el_line.lastchar)
			*el->el_line.cursor++ = c;
		re_refresh(el);
	}

	if (el->el_state.inputmode == MODE_REPLACE_1)
		return vi_command_mode(el, 0);

	return CC_NORM;
}
