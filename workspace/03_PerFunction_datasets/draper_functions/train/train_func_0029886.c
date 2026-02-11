laststring(char *linebuf, int *flag, int strip)
{
	char *cp, *p;
	char quoted;

	*flag = 1;
	cp = strlen(linebuf) + linebuf - 1;


	while (cp > linebuf && whitechar(*cp & 0377))
		cp--;
	*++cp = 0;
	if (cp == linebuf) {
		*flag = 0;
		return NULL;
	}


	quoted = *(cp - 1);
	if (quoted == '\'' || quoted == '\"') {
		cp--;
		if (strip)
			*cp = '\0';
		cp--;
		while (cp > linebuf) {
			if (*cp != quoted) {
				cp--;
			} else if (*(cp - 1) != '\\') {
				break;
			} else {
				p = --cp;
				do {
					*p = *(p + 1);
				} while (*p++);
				cp--;
			}
		}
		if (cp == linebuf)
			*flag = 0;
		if (*cp == quoted) {
			if (strip)
				*cp++ = 0;
		} else
			*flag = 0;
	} else {
		while (cp > linebuf && !whitechar(*cp & 0377))
			cp--;
		if (whitechar(*cp & 0377))
			*cp++ = 0;
		else
			*flag = 0;
	}
	if (*cp == '\0') {
		return(NULL);
	}
	return(cp);
}
