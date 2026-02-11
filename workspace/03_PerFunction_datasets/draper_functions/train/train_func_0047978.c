expandbuffer(Buffer *buf, size_t minsize) {
	buf->len += (minsize > buf->len) ? minsize : buf->len;
	buf = erealloc(buf, offsetof(Buffer, str[buf->len]));
	return buf;
}
