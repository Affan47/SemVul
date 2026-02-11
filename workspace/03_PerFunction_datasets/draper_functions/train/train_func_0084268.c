php_stdiop_seek(php_stream *stream, off_t offset, int whence, off_t *newoffset TSRMLS_DC)
{
	php_stdio_stream_data *data = (php_stdio_stream_data*)stream->abstract;
	int ret;

	assert(data != NULL);

	if (data->is_pipe) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "cannot seek on a pipe");
		return -1;
	}

	if (data->fd >= 0) {
		off_t result;

		result = lseek(data->fd, offset, whence);
		if (result == (off_t)-1)
			return -1;

		*newoffset = result;
		return 0;

	} else {
		ret = fseek(data->file, offset, whence);
		*newoffset = ftell(data->file);
		return ret;
	}
}
