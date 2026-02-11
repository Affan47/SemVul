git_filebuf_reserve(git_filebuf *file, void **buffer, size_t len)
{
	int error;
	size_t space_left = file->buf_size - file->buf_pos;

	*buffer = NULL;

	if (len > file->buf_size)
		return GIT_ENOMEM;

	if (space_left <= len) {
		if ((error = flush_buffer(file)) < GIT_SUCCESS)
			return error;
	}

	*buffer = (file->buffer + file->buf_pos);
	file->buf_pos += len;

	return GIT_SUCCESS;
}
