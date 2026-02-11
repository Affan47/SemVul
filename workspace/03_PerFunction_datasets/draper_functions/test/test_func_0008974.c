write_hex_n_on_level(unsigned int loglevel, unsigned long num)
{
	unsigned char *s = (unsigned char *)&num;
	unsigned char c;
	int i;

	if (loglevel > current_loglevel)
		return;

	c = 'x';
	sys_write(current_logfd, &c, 1);
	for (i = sizeof(long)/sizeof(char) - 1; i >= 0; i--) {
		c = (s[i] & 0xf0) >> 4;
		__add_ord(c);
		sys_write(current_logfd, &c, 1);

		c = (s[i] & 0x0f);
		__add_ord(c);
		sys_write(current_logfd, &c, 1);
	}

	c = '\n';
	sys_write(current_logfd, &c, 1);
}
