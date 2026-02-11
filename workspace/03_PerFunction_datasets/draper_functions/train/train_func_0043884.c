gz_file_open(struct output_file *out, int fd)
{
	struct output_file_gz *outgz = to_output_file_gz(out);

	outgz->gz_fd = gzdopen(fd, "wb9");
	if (!outgz->gz_fd) {
		error_errno("gzopen");
		return -errno;
	}

	return 0;
}
