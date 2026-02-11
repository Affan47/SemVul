packet_read_line(int fd, char *buffer, unsigned size)
{
	int n;
	unsigned len;
	char linelen[4];

	safe_read(fd, linelen, 4);

	len = 0;
	for (n = 0; n < 4; n++) {
		unsigned char c = linelen[n];
		len <<= 4;
		if (c >= '0' && c <= '9') {
			len += c - '0';
			continue;
		}
		if (c >= 'a' && c <= 'f') {
			len += c - 'a' + 10;
			continue;
		}
		if (c >= 'A' && c <= 'F') {
			len += c - 'A' + 10;
			continue;
		}
		die("protocol error: bad line length character");
	}
	if (!len)
		return 0;
	len -= 4;
	if (len >= size)
		die("protocol error: bad line length %d", len);
	safe_read(fd, buffer, len);
	buffer[len] = 0;
	return len;
}
