char_read (char *bytes, int size, int read_timeout)
{
	struct timeval serial_timeout;
	fd_set readfs;
	int readen = 0;
	int rc = 0;

	FD_ZERO (&readfs);
	FD_SET (upsfd, &readfs);

	serial_timeout.tv_usec = (read_timeout % 1000) * 1000;
	serial_timeout.tv_sec = (read_timeout / 1000);

	rc = select (upsfd + 1, &readfs, NULL, NULL, &serial_timeout);
	if (0 == rc)
		return -2;

	if (FD_ISSET (upsfd, &readfs)) {
		int now = read (upsfd, bytes, size - readen);

		if (now < 0) {
			return -1;
		}
		else {
			bytes += now;
			readen += now;
		}
	}
	else {
		return -1;
	}
	return readen;
}
