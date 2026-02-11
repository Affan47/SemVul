roman2str(buf, s, size)
char *buf;
CONST char *s;
ALLOC_T size;
{
	ALLOC_T ptr, len;
	int i, n;

	ptr = (ALLOC_T)0;
	while (size) {
#ifdef	FAKEUNINIT
		n = 0;
#endif
		for (len = size; len > (ALLOC_T)0; len--)
			if ((n = searchroman(s, len)) >= 0) break;
		if (len <= (ALLOC_T)0) {
			if (*s == 'n') ptr += Xjis2str(&(buf[ptr]), J_NN);
			else if (*s == '-')
				ptr += Xjis2str(&(buf[ptr]), J_CHO);
			else if (*s == *(s + 1))
				ptr += Xjis2str(&(buf[ptr]), J_TSU);

			s++;
			size--;
			continue;
		}

		for (i = 0; i < R_MAXKANA; i++) {
			if (!romanlist[n].code[i]) break;
			ptr += Xjis2str(&(buf[ptr]), romanlist[n].code[i]);
		}
		s += len;
		size -= len;
	}
	buf[ptr] = '\0';
}
