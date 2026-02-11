write_file_chunk(struct output_file *out, unsigned int len,
		const char *file, int64_t offset)
{
	int ret;

	int file_fd = open(file, O_RDONLY | O_BINARY);
	if (file_fd < 0) {
		return -errno;
	}

	ret = write_fd_chunk(out, len, file_fd, offset);

	close(file_fd);

	return ret;
}
