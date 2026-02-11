move(int l, int m)
{
	register wchar_t *cp, *dp;

	for (cp = page[l], dp = page[m]; *cp; cp++, dp++) {
		switch (*cp) {
			case '|':
				if (*dp != ' ' && *dp != '|' && *dp != 0)
					return;
				break;
			case ' ':
				break;
			default:
				return;
		}
	}
	if (*cp == 0) {
		for (cp = page[l], dp = page[m]; *cp; cp++, dp++)
			if (*cp == '|')
				*dp = '|';
			else if (*dp == 0)
				*dp = ' ';
		page[l][0] = 0;
	}
}
