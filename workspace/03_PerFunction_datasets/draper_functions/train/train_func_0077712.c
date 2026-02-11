ctlfile_appendvfd(int fd, const struct iovec *iov, int iovcnt)
{
int	l=0;
int	i;

	for (i=0; i<iovcnt; i++)
		l += iov[i].iov_len;

	if (writev(fd, iov, iovcnt) != l)	notatomic();
}
