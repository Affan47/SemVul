file_pad(struct output_file *out, int64_t len)
{
	int ret;
	struct output_file_normal *outn = to_output_file_normal(out);

	ret = ftruncate64(outn->fd, len);
	if (ret < 0) {
		return -errno;
	}

	return 0;
}
