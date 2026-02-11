git_buf_cstr(git_buf *buf)
{
	if (buf->size + 1 >= buf->asize && git_buf_grow(buf, buf->size + 1) < GIT_SUCCESS)
		return NULL;

	buf->ptr[buf->size] = '\0';
	return buf->ptr;
}
