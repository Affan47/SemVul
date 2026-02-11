decode_dollar_squote(void)
{
	static const char C_escapes[] ALIGN1 = "nrbtfav""x\\01234567";
	int c, cnt;
	char *p;
	char buf[4];

	c = pgetc();
	p = strchr(C_escapes, c);
	if (p) {
		buf[0] = c;
		p = buf;
		cnt = 3;
		if ((unsigned char)(c - '0') <= 7) {
			do {
				c = pgetc();
				*++p = c;
			} while ((unsigned char)(c - '0') <= 7 && --cnt);
			pungetc();
		} else if (c == 'x') {
			do {
				c = pgetc();
				*++p = c;
			} while (isxdigit(c) && --cnt);
			pungetc();
			if (cnt == 3) {
				c = 'x';
				goto unrecognized;
			}
		} else {
			p++;
		}
		*p = '\0';
		p = buf;
		c = bb_process_escape_sequence((void*)&p);
	} else {
		if (c != '\'' && c != '"') {
 unrecognized:
			c |= 0x100;
		}
	}
	return c;
}
