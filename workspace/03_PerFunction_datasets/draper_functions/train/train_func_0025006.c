unpacksms8(unsigned char *i, unsigned char l, unsigned char *udh, int *udhl, unsigned short *ud, int *udl, char udhi)
{
	unsigned short *o = ud;
	*udhl = 0;
	if (udhi) {
		int n = *i;
		*udhl = n;
		if (n) {
			i++;
			l--;
			while (l && n) {
				l--;
				n--;
				*udh++ = *i++;
			}
		}
	}
	while (l--) {
		*o++ = *i++;
	}
	*udl = (o - ud);
}
