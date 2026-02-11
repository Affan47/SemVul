Fdopen(int fd, const char *mode)
{
	FILE *fp;
	int	omode;

	scan_mode(mode, &omode);
	if ((fp = fdopen(fd, mode)) != NULL) {
		register_file(fp, omode, 0, 0, FP_UNCOMPRESSED, NULL, 0L);
		fcntl(fileno(fp), F_SETFD, FD_CLOEXEC);
	}
	return fp;
}
