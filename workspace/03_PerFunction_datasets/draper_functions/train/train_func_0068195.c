StrLength()
{
	static const char	inquotes[] = "Where are the quotes?";
	char	*cp;
	int	numchars = 0;

	for (cp = linebuf+curchar; ; cp--) {
		if (*cp == '"' && (cp == linebuf || cp[-1] != '\\'))
			break;

		if (cp == linebuf)
			complain(inquotes);
	}

	cp += 1;
	for (;;) {
		switch (*cp++) {
		case '\0':
			complain(inquotes);

		case '"':
			f_mess("%d characters", numchars);
			stickymsg = YES;
			return;
		case '\\':
			if (!jisdigit(*cp)) {
				if (*cp == '\0')
					complain(inquotes);
				cp += 1;
			} else {
				int	num = 3;

				do cp += 1; while (--num != 0 && jisdigit(*cp));
			}
			break;
		}
		numchars += 1;
	}
}
