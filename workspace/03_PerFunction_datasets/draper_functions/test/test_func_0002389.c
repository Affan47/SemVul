safe_write(int fd, const void* buf, size_t count)
{
	int ret;
	do
	{
		ret = write(fd, buf, count);
	} while (ret == -1 && errno == EINTR);

	return ret;
}
