git_buf_detach(git_buf *buf)
{
	char *data = buf->ptr;

	if (buf->asize == 0 || buf->ptr == git_buf__oom)
		return NULL;

	git_buf_init(buf, 0);

	return data;
}
