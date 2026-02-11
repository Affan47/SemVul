git_buf_vprintf(git_buf *buf, const char *format, va_list ap)
{
	int len;
	const size_t expected_size = buf->size + (strlen(format) * 2);

	ENSURE_SIZE(buf, expected_size);

	while (1) {
		va_list args;
		va_copy(args, ap);

		len = p_vsnprintf(
			buf->ptr + buf->size,
			buf->asize - buf->size,
			format, args
		);

		if (len < 0) {
			git__free(buf->ptr);
			buf->ptr = git_buf__oom;
			return -1;
		}

		if ((size_t)len + 1 <= buf->asize - buf->size) {
			buf->size += len;
			break;
		}

		ENSURE_SIZE(buf, buf->size + len + 1);
	}

	return 0;
}
