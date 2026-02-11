system_pread(int fd, void *buf, size_t buflen, off_t offset)
{
	return initIfNeeded() == 0 ? s_pread( fd, buf, buflen, offset) : -1;
}
