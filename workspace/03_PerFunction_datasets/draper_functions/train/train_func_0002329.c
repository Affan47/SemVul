buffer_append_string_rfill(buffer *b, const char *s, size_t maxlen) {
	size_t s_len;

	if (!s || !b) return -1;

	s_len = strlen(s);
	if (s_len > maxlen)  s_len = maxlen;
	buffer_prepare_append(b, maxlen + 1);
	if (b->used == 0)
		b->used++;

	memcpy(b->ptr + b->used - 1, s, s_len);
	if (maxlen > s_len) {
		memset(b->ptr + b->used - 1 + s_len, ' ', maxlen - s_len);
	}

	b->used += maxlen;
	b->ptr[b->used - 1] = '\0';
	return 0;
}
