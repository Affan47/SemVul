get_word_under_cursor() {
	Filerange word = text_object_word(vis->win->text->data, window_cursor_get(vis->win->win));
	if (!text_range_valid(&word))
		return NULL;
	size_t len = word.end - word.start;
	char *buf = malloc(len+1);
	if (!buf)
		return NULL;
	len = text_bytes_get(vis->win->text->data, word.start, len, buf);
	buf[len] = '\0';
	return buf;
}
