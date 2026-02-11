c_insert(EditLine *el, int num)
{
	Char *cp;

	if (el->el_line.lastchar + num >= el->el_line.limit) {
		if (!ch_enlargebufs(el, (size_t)num))
			return;
	}

	if (el->el_line.cursor < el->el_line.lastchar) {

		for (cp = el->el_line.lastchar; cp >= el->el_line.cursor; cp--)
			cp[num] = *cp;
	}
	el->el_line.lastchar += num;
}
