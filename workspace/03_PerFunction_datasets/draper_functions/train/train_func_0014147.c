strisnum(char *s)
{
	int digits = 0;

	while(isspace(*s))
		s++;
	if (*s == '-')
		s++;
	while(*s) {
		if (isspace(*s)) {
			while(isspace(*s))
				s++;
			if (*s) return 0;
			return digits ? 1 : 0;
		}
		if (!isdigit(*s))
			return 0;
		s++;
		digits++;
	}
	return digits ? 1 : 0;
}
