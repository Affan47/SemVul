_buffer_extendby(struct buffer *b, int len)
{
	char* buffer;

	len += b->NUL;
	if (len <= b->buflen)
		return;

	if (!b->buflen)
		b->buflen = 32;

	b->buflen = _next_power(len);
	buffer = realloc(b->buf, b->buflen);
	b->buf = buffer;
}
