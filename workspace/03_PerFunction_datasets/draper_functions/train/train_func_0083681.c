copy_from_stdin(void)
{
	int	c, bad_read = 0;

	while (1) {
		c = do_read(0);
		if ((c == 0 ) ||
		    ((c < 0) && ((errno == EAGAIN) || (errno == EINTR)))) {
			if (bad_read++ > 3)
				break;
			continue;
		}
		if (c < 0) {
			perror("read");
			exit(1);
		}
		bad_read = 0;
	}
	return 0;
}
