ed_transpose_chars(EditLine *el, Int c)
{

	if (el->el_line.cursor < el->el_line.lastchar) {
		if (el->el_line.lastchar <= &el->el_line.buffer[1])
			return (CC_ERROR);
		else
			el->el_line.cursor++;
	}
	if (el->el_line.cursor > &el->el_line.buffer[1]) {

		c = el->el_line.cursor[-2];
		el->el_line.cursor[-2] = el->el_line.cursor[-1];
		el->el_line.cursor[-1] = c;
		return (CC_REFRESH);
	} else
		return (CC_ERROR);
}
