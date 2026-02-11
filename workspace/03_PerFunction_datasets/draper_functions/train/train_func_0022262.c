git_filebuf_write(git_filebuf *file, const void *buff, size_t len)
{
	int error;
	const unsigned char *buf = buff;

	for (;;) {
		size_t space_left = file->buf_size - file->buf_pos;


		if (space_left > len) {
			add_to_cache(file, buf, len);
			return GIT_SUCCESS;
		}


		if (file->buf_pos > 0) {
			add_to_cache(file, buf, space_left);

			if ((error = flush_buffer(file)) < GIT_SUCCESS)
				return git__rethrow(error, "Failed to write to buffer");

			len -= space_left;
			buf += space_left;
		}


		if (len > file->buf_size) {
			error = file->write(file, buf, len);
			if (error < GIT_SUCCESS)
				return git__rethrow(error, "Failed to write to buffer");
			return GIT_SUCCESS;
		}
	}
}
