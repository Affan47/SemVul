getscanwhite(FILE *fp, BOOL skip, unsigned int width, int scannum, char **strptr)
{
	char *str;
	unsigned long len;
	unsigned long totlen;
	char buf[READSIZE];
	int c;
	char *b;
	BOOL comp;
	unsigned int chnum;

	totlen = 0;
	str = NULL;

	comp = (scannum < 0);
	if (comp)
		scannum = -scannum;

	chnum = 0;

	for (;;) {
		len = 0;
		b = buf;
		for(;;) {
			c = fgetc(fp);
			if (c == EOF || c == '\0')
				break;
			chnum++;
			if(scannum && (!isspace(c) ^ comp))
				break;
			if (!skip) {
				*b++ = c;
				len++;
				if (len >= READSIZE)
					break;
			}
			if (chnum == width)
				break;
		}
		if (!skip) {
			if (totlen)
				str = (char *) realloc(str, totlen + len + 1);
			else
				str = (char *) malloc(len + 1);
			if (str == NULL) {
				math_error("Out of memory for scanning");

			}
			if (len)
				memcpy(&str[totlen], buf, len);
			totlen += len;
		}
		if (len < READSIZE)
			break;
	}

	if (!(width && chnum == width) && c != '\0')
		ungetc(c, fp);

	if (!skip) {
		str[totlen] = '\0';
		*strptr = str;
	}
}
