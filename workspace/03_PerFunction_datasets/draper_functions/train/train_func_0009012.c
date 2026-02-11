el_cursor(EditLine *el, int n)
{
	if (n == 0)
		goto out;

	el->el_line.cursor += n;

	if (el->el_line.cursor < el->el_line.buffer)
		el->el_line.cursor = el->el_line.buffer;
	if (el->el_line.cursor > el->el_line.lastchar)
		el->el_line.cursor = el->el_line.lastchar;
out:
	return el->el_line.cursor - el->el_line.buffer;
}
