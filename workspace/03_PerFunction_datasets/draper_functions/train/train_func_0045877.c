git_buf_putc(git_buf *buf, char c)
{
	ENSURE_SIZE(buf, buf->size + 2);
	buf->ptr[buf->size++] = c;
	buf->ptr[buf->size] = '\0';
	return 0;
}
