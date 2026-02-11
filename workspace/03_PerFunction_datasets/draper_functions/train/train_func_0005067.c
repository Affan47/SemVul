fmtappend(Format *format, const char *s, size_t len) {
	while (format->buf + len > format->bufend) {
		size_t split = format->bufend - format->buf;
		memcpy(format->buf, s, split);
		format->buf += split;
		s += split;
		len -= split;
		(*format->grow)(format, len);
	}
	memcpy(format->buf, s, len);
	format->buf += len;
}
