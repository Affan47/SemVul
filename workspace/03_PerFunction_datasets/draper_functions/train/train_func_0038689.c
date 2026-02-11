apc_write(unsigned char code)
{
	errno = 0;
	if (upsfd == -1)
		return 0;
	return ser_send_char(upsfd, code);
}
