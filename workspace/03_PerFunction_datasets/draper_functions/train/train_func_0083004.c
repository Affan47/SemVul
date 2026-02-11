packfile_unpack_header1(
		size_t *sizep,
		git_otype *type,
		const unsigned char *buf,
		unsigned long len)
{
	unsigned shift;
	unsigned long size, c;
	unsigned long used = 0;

	c = buf[used++];
	*type = (c >> 4) & 7;
	size = c & 15;
	shift = 4;
	while (c & 0x80) {
		if (len <= used || bitsizeof(long) <= shift)
			return 0;

		c = buf[used++];
		size += (c & 0x7f) << shift;
		shift += 7;
	}

	*sizep = (size_t)size;
	return used;
}
