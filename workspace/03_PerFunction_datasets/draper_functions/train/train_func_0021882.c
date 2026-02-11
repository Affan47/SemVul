stepd_signal_container(int fd, int signal)
{
	int req = REQUEST_SIGNAL_CONTAINER;
	int rc;
	int errnum = 0;

	safe_write(fd, &req, sizeof(int));
	safe_write(fd, &signal, sizeof(int));


	safe_read(fd, &rc, sizeof(int));
	safe_read(fd, &errnum, sizeof(int));

	errno = errnum;
	return rc;
rwfail:
	return -1;
}
