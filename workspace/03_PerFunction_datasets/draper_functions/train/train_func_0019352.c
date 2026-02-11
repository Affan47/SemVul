__write_cpio_header(int fd, size_t size)
{
	char fn[] = LINUX_CPIO_UCODE_NAME;
	char *p1, *p2;
	int s = 0;
	int r;

	p1 = fn;
	do {
		p2 = strchr(p1, '/');
		if (p2) {
			*p2 = 0;
			r = __write_cpio_hdrentry(fd, fn, 0);
			if (r < 0)
				return r;
			s += r;
			*p2 = '/';
			p1 = ++p2;
		}
	} while (p2);

	r = __write_cpio_hdrentry(fd, fn, size);
	if (r < 0)
		return r;

	s += r;
	return s;
}
