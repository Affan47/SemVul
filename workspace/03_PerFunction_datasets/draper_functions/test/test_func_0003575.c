drainSelfPipe(void)
{


	char buf[16];
	int rc;

	for (;;)
	{
		rc = read(selfpipe_readfd, buf, sizeof(buf));
		if (rc < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break;
			else if (errno == EINTR)
				continue;
			else
				elog(ERROR, "read() on self-pipe failed: %m");
		}
		else if (rc == 0)
			elog(ERROR, "unexpected EOF on self-pipe");
	}
}
