text_line_prev(Text *txt, size_t pos) {
	char c;
	Iterator it = text_iterator_get(txt, pos);
	if (!text_iterator_byte_get(&it, &c))
		return pos;
	if (c == '\n')
		text_iterator_byte_prev(&it, &c);
	if (c == '\r')
		text_iterator_byte_prev(&it, &c);
	while (text_iterator_byte_get(&it, &c) && c != '\n')
		text_iterator_byte_prev(&it, NULL);
	if (text_iterator_byte_prev(&it, &c) && c != '\r')
		text_iterator_byte_next(&it, &c);
	return it.pos;
}
