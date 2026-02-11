in_ether(const char *bufp, struct sockaddr *sap)
{
	char *ptr;
	int i, j;
	unsigned char val;
	unsigned char c;

	sap->sa_family = ARPHRD_ETHER;
	ptr = (char *) sap->sa_data;

	i = 0;
	do {
		j = val = 0;


		if (i && (*bufp == ':')) {
			bufp++;
		}

		do {
			c = *bufp;
			if (((unsigned char)(c - '0')) <= 9) {
				c -= '0';
			} else if (((unsigned char)((c|0x20) - 'a')) <= 5) {
				c = (c|0x20) - ('a'-10);
			} else if (j && (c == ':' || c == 0)) {
				break;
			} else {
				return -1;
			}
			++bufp;
			val <<= 4;
			val += c;
		} while (++j < 2);
		*ptr++ = val;
	} while (++i < ETH_ALEN);

	return *bufp;
}
