freadfile(FILE *f, char **pp)
{
	size_t bs;
	size_t bf;
	size_t bu = 0;
	char *buffer, *nb;
	size_t rv;
	int old_errno = errno;

	bs = BUFSIZ;
	bf = bs;
	buffer = malloc(bs);

	if (!buffer)
		return -1;

	for (;;) {
		errno = 0;

		while (bf && (rv = _fread(buffer + bu, bf, f))) {
			bu += rv;
			bf -= rv;
		}

		if (errno && errno != EINTR && errno != EAGAIN) {

			free(buffer);
			return -1;
		}

		if (bf) {


			if ((nb = realloc(buffer, bu + 1)))
				buffer = nb;


			buffer[bu] = '\0';

			*pp = buffer;
			errno = old_errno;
			return bu;
		}


		bf += bs;
		bs += bs;
		if (!(nb = realloc(buffer, bs))) {

			free(buffer);
			return -1;
		}
		buffer = nb;
	}
}
