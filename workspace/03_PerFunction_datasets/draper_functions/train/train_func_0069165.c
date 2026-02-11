sa_read(void *buffer, int size)
{
	int n;

	while (size) {

		if ((n = read(STDIN_FILENO, buffer, size)) < 0) {
			perror("read");
			exit(2);
		}

		if (!n)
			return 1;

		size -= n;
		buffer = (char *) buffer + n;
	}

	return 0;
}
