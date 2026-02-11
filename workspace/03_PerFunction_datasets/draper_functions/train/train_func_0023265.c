signal_pending(void)
{
	fd_set readset;
	int rc;
	struct timeval timeout = { 0, 0 };

	FD_ZERO(&readset);
	FD_SET(signal_pipe[0], &readset);

	rc = select(signal_pipe[0] + 1, &readset, NULL, NULL, &timeout);

	return rc>0?1:0;
}
