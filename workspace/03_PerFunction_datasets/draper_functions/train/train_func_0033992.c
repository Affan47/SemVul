socket_getline (char *str, size_t size, int sock, unsigned int timeout)
{
	char c, *ptr = str;
	int r;

	while(socket_wait_io(sock, timeout) > 0) {
		if ((r = read(sock, &c, 1)) != 0) {
			if (r < 0)
				return -1;

			if ((ptr - str) >= size)
				break;

			*(ptr++) = c;

			if (c == '\n')
				break;
		} else { return -1; }
	}
	*ptr = '\0';
	return (ptr - str);
}
