newabbr(const char *const string)
{
	register int	i;

	if (strcmp(string, GRANDPARENTED) != 0) {
		register const char *	cp;
		const char *		mp;


		cp = string;
		mp = NULL;
		while (isascii((unsigned char) *cp) &&
			isalpha((unsigned char) *cp))
				++cp;
		if (cp - string == 0)
mp = _("time zone abbreviation lacks alphabetic at start");
		if (noise && cp - string < 3)
mp = _("time zone abbreviation has fewer than 3 alphabetics");
		if (cp - string > ZIC_MAX_ABBR_LEN_WO_WARN)
mp = _("time zone abbreviation has too many alphabetics");
		if (mp == NULL && (*cp == '+' || *cp == '-')) {
			++cp;
			if (isascii((unsigned char) *cp) &&
				isdigit((unsigned char) *cp))
					if (*cp++ == '1' &&
						*cp >= '0' && *cp <= '4')
							++cp;
		}
		if (*cp != '\0')
mp = _("time zone abbreviation differs from POSIX standard");
		if (mp != NULL)
			warning("%s (%s)", mp, string);
	}
	i = strlen(string) + 1;
	if (charcnt + i > TZ_MAX_CHARS) {
		error(_("too many, or too long, time zone abbreviations"));
		exit(EXIT_FAILURE);
	}
	(void) strcpy(&chars[charcnt], string);
	charcnt += i;
}
