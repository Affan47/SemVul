seek_func_fd(off_t pos, void *ptr)
{
	struct rfc2045src_fd *s=(struct rfc2045src_fd *)ptr;

	if (lseek(s->fd, pos, SEEK_SET) < 0)
		return -1;

	return 0;
}
