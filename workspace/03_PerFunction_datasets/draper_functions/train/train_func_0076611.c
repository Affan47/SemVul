hexstring_a2n(const char *str, __u8 *buf, int blen)
{
	int cnt = 0;

	for (;;) {
		unsigned acc;
		char ch;

		acc = 0;

		while ((ch = *str) != ':' && ch != 0) {
			if (ch >= '0' && ch <= '9')
				ch -= '0';
			else if (ch >= 'a' && ch <= 'f')
				ch -= 'a'-10;
			else if (ch >= 'A' && ch <= 'F')
				ch -= 'A'-10;
			else
				return NULL;
			acc = (acc<<4) + ch;
			str++;
		}

		if (acc > 255)
			return NULL;
		if (cnt < blen) {
			buf[cnt] = acc;
			cnt++;
		}
		if (ch == 0)
			break;
		++str;
	}
	if (cnt < blen)
		memset(buf+cnt, 0, blen-cnt);
	return buf;
}
