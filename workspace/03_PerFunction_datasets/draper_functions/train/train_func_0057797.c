gz_file_pad(struct output_file *out, int64_t len)
{
	off64_t ret;
	struct output_file_gz *outgz = to_output_file_gz(out);

	ret = gztell(outgz->gz_fd);
	if (ret < 0) {
		return -1;
	}

	if (ret >= len) {
		return 0;
	}

	ret = gzseek(outgz->gz_fd, len - 1, SEEK_SET);
	if (ret < 0) {
		return -1;
	}

	gzwrite(outgz->gz_fd, "", 1);

	return 0;
}
