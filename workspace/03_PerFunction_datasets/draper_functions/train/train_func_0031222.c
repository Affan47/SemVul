cavan_tty_redirect_loop(int ttyfd, int ttyin, int ttyout)
{
	int ret;
	ssize_t rdlen;
	char buff[1024];
	struct pollfd pfds[2];

	pfds[0].events = POLLIN;
	pfds[0].fd = ttyin;

	pfds[1].events = POLLIN;
	pfds[1].fd = ttyfd;

	while (1)
	{
		ret = poll(pfds, NELEM(pfds), -1);
		if (ret <= 0)
		{
			return -ETIMEDOUT;
		}

		if (pfds[0].revents)
		{
			rdlen = read(ttyin, buff, sizeof(buff));
			if (rdlen <= 0 || write(ttyfd, buff, rdlen) < rdlen)
			{
				break;
			}
		}

		if (pfds[1].revents)
		{
			rdlen = read(ttyfd, buff, sizeof(buff));
			if (rdlen <= 0 || write(ttyout, buff, rdlen) < rdlen)
			{
				break;
			}

			fsync(ttyout);
		}
	}

	return 0;
}
