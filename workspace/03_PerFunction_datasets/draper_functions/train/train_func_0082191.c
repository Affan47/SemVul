parse_string(const char **ptr, char **val)
{
	const size_t bufsize = 256;
	char _buf[bufsize];
	char *buf = _buf;
	size_t alloc = bufsize;
	char delim = **ptr;
	size_t idx = 0;
	(*ptr)++;
	while (1) {
		int c = **ptr;
		switch (c) {
		case '\0':
			SNDERR("Unterminated string");
			return -EINVAL;
		case '\\':
			c = parse_char(ptr);
			if (c < 0)
				return c;
			break;
		default:
			(*ptr)++;
			if (c == delim) {
				*val = malloc(idx + 1);
				if (!*val)
					return -ENOMEM;
				memcpy(*val, buf, idx);
				(*val)[idx] = 0;
				if (alloc > bufsize)
					free(buf);
				return 0;
			}
		}
		if (idx >= alloc) {
			size_t old_alloc = alloc;
			alloc *= 2;
			if (old_alloc == bufsize) {
				buf = malloc(alloc);
				memcpy(buf, _buf, old_alloc);
			} else {
				buf = realloc(buf, alloc);
			}
			if (!buf)
				return -ENOMEM;
		}
		buf[idx++] = c;
	}
}
