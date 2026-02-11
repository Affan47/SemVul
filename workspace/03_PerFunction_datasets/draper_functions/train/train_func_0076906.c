fts_safe_changedir(sp, p, fd, path)
	const FTS *sp;
	const FTSENT *p;
	int fd;
	const char *path;
{
	int oldfd = fd, ret = -1;
	struct STAT sb;

	if (ISSET(FTS_NOCHDIR))
		return 0;

	if (fd < 0 && (fd = open(path, O_RDONLY)) == -1)
		return -1;

	if (fstat(fd, &sb) == -1)
		goto bail;

	if (sb.st_ino != p->fts_ino || sb.st_dev != p->fts_dev) {
		errno = ENOENT;
		goto bail;
	}

	ret = fchdir(fd);

bail:
	if (oldfd < 0) {
		int save_errno = errno;
		(void)close(fd);
		errno = save_errno;
	}
	return ret;
}
