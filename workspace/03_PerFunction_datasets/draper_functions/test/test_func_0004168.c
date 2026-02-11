get_random()
{
	static uint8_t buf[128];
	static int pos = 0;
	int r;

	if (pos == 0)
		read(urandom_fd, buf, 128);

	r = buf[pos++];

	if (pos == 128)
		pos = 0;

	return r;
}
