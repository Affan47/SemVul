buffer_append_space(Buffer *buffer, size_t len)
{
	size_t newlen;
	void *p;

	if (len > 0x100000) {
		Display(LOG_LEVEL_1, ELError, "buffer_append_space", GOGO_STR_LEN_NOT_SUPPORTED, len);
		exit(-1);
	}

	if (buffer->offset == buffer->end) {
		buffer->offset = 0;
		buffer->end = 0;
	}
restart:

	if (buffer->end + len < buffer->alloc) {
		p = buffer->buf + buffer->end;
		buffer->end += len;
		return p;
	}


	if (buffer->offset > buffer->alloc / 2) {
		memmove(buffer->buf, buffer->buf + buffer->offset,
			buffer->end - buffer->offset);
		buffer->end -= buffer->offset;
		buffer->offset = 0;
		goto restart;
	}

	newlen = buffer->alloc + len + 32768;
	if (newlen > 0xa00000) {
		Display(LOG_LEVEL_1, ELError, "buffer_append_space", GOGO_STR_ALLOC_NOT_SUPPORTED, newlen);
		exit(-1);
	}
	buffer->buf = realloc(buffer->buf, newlen);
	buffer->alloc = newlen;
	goto restart;

}
