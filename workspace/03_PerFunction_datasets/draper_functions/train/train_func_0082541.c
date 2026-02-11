cistrstr(const char *s, const char *sub) {
	int c, csub;
	unsigned int len;

	if(!sub)
		return (char *)s;
	if((c = *sub++) != 0) {
		c = tolower(c);
		len = strlen(sub);
		do {
			do {
				if((csub = *s++) == 0)
					return NULL;
			}
			while(tolower(csub) != c);
		}
		while(strncasecmp(s, sub, len) != 0);
		s--;
	}
	return (char *)s;
}
