try_create_file(const char *path, unsigned int mode, const char *buf, unsigned long size)
{
	int fd;
	char *nbuf;

	if (has_symlinks && S_ISLNK(mode))


		return symlink(buf, path);

	fd = open(path, O_CREAT | O_EXCL | O_WRONLY, (mode & 0100) ? 0777 : 0666);
	if (fd < 0)
		return -1;

	nbuf = convert_to_working_tree(path, buf, &size);
	if (nbuf)
		buf = nbuf;

	while (size) {
		int written = xwrite(fd, buf, size);
		if (written < 0)
			die("writing file %s: %s", path, strerror(errno));
		if (!written)
			die("out of space writing file %s", path);
		buf += written;
		size -= written;
	}
	if (close(fd) < 0)
		die("closing file %s: %s", path, strerror(errno));
	if (nbuf)
		free(nbuf);
	return 0;
}
