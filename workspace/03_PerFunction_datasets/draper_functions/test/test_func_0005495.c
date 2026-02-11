_php_stream_getc(php_stream *stream TSRMLS_DC)
{
	char buf;

	if (php_stream_read(stream, &buf, 1) > 0) {
		return buf & 0xff;
	}
	return EOF;
}
