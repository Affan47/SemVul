create_lock(
    char *fn,
    long pid)
{
	int fd;
	FILE *f;
	int mask;

	(void)delete_lock(fn);

	mask = umask(0027);
	fd = open(fn, O_WRONLY | O_CREAT | O_EXCL, 0640);
	umask(mask);
	if (fd == -1) return -1;

	if((f = fdopen(fd, "w")) == NULL) {
	    aclose(fd);
	    return -1;
	}
	g_fprintf(f, "%ld\n", pid);
	if (fclose(f) == EOF)
	    return -1;
	return 0;
}
