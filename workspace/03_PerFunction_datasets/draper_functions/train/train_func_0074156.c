wait(int timeout) const
{
	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(wait_pipe[0], &rfds);

	timeval tv;
	tv.tv_sec = timeout/1000;
	tv.tv_usec = (timeout%1000)*1000;

	int result = select(wait_pipe[0]+1, &rfds, NULL, NULL, (timeout == -1) ? NULL : &tv);
	if (result <= 0) return false;

	return true;
}
