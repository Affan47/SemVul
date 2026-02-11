text_line_lastchar(Text *txt, size_t pos) {
	char c;
	Iterator it = text_iterator_get(txt, text_line_end(txt, pos));
	if (text_iterator_char_prev(&it, &c) && c == '\n')
		text_iterator_byte_next(&it, NULL);
	return it.pos;
}
