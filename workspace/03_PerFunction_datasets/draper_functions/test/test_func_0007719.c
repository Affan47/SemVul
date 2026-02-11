file_sync_fclose(FILE *f)
{
	int fd, ret;

	g_assert(f != NULL);

	ret = fflush(f);
	fd = fileno(f);

	if (-1 == fd_fdatasync(fd))
		s_warning("cannot flush data blocks to disk for fd=%d: %m", fd);

	return fclose(f) | ret;
}
