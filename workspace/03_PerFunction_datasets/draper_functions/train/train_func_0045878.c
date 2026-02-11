readnoecho(char* buf, int maxl)
{
	char c = 0;
	int n, i = 0;

	echo_disable();
	while (c != '\n') {
		n = read(STDIN_FILENO, &c, 1);
		if (n == -1 && (errno == EAGAIN || errno == EINTR))
			continue;
		if (n != 1)
			break;
		if (c == '\r')
			break;
		if (c == '\n')
			break;
		if (i < maxl)
			buf[i++] = c;
	}
	buf[i] = '\0';
	echo_restore();
	fprintf(stderr, "\n");
	fflush(stderr);
	return i;
}
