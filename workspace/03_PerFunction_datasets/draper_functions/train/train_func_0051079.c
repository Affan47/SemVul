do_readlink(const char *path, char *buf, size_t bufsiz)
{

	if (am_root < 0) {
		int fd = do_open_nofollow(path, O_RDONLY);
		if (fd >= 0) {
			int len = read(fd, buf, bufsiz);
			close(fd);
			return len;
		}
		if (errno != ELOOP)
			return -1;


		if (!am_sender)
			return 0;

	}

	return readlink(path, buf, bufsiz);
}
