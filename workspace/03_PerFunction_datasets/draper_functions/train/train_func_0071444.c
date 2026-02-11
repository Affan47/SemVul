packet_read_line(int fd, char *buffer, unsigned size)
{
	int len;
	char linelen[4];

	safe_read(fd, linelen, 4);
	len = packet_length(linelen);
	if (len < 0)
		die("protocol error: bad line length character: %.4s", linelen);
	if (!len) {
		packet_trace("0000", 4, 0);
		return 0;
	}
	len -= 4;
	if (len >= size)
		die("protocol error: bad line length %d", len);
	safe_read(fd, buffer, len);
	buffer[len] = 0;
	packet_trace(buffer, len, 0);
	return len;
}
