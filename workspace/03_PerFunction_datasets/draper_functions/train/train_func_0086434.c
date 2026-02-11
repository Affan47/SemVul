write_log(int logfd, const char *buffer, size_t bytes)
{
	const char *p = buffer;

	while ((size_t)(p - buffer) < bytes) {
		switch (*p) {
		case '\r':
			goto cont;
		case '\033':
			in_escape = true;
			in_term = false;
			goto cont;
		case '\n':
			in_escape = in_term = false;
			break;
		case '[':
			if (in_escape)
				in_term = true;
			break;
		}

		if (!in_escape) {
			if (write(logfd, p++, 1) == -1)
				eerror("write: %s", strerror(errno));
			continue;
		}

		if (! in_term || isalpha((unsigned char)*p))
			in_escape = in_term = false;
cont:
		p++;
	}
}
