check_ax25_addr(unsigned char *buf)
{
	int k;
	unsigned char c;


	for (k = 0; k < 6; k++) {
		c = buf[k] >> 1;
		if (c == ' ')
			break;
		if ((c < 'A' || c > 'Z') && (c < '0' || c > '9'))
			return 1;
	}


	if (k == 0)
		return 1;


	for (k++; k < 6; k++)
		if (buf[k] >> 1 != ' ')
			return 1;

	return 0;
}
