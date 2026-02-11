my_strtod(char **pp)
{
	char *cp = *pp;
	if (ENABLE_DESKTOP && cp[0] == '0') {

		char c = (cp[1] | 0x20);
		if (c == 'x' || isdigit(cp[1])) {
			unsigned long long ull = strtoull(cp, pp, 0);
			if (c == 'x')
				return ull;
			c = **pp;
			if (!isdigit(c) && c != '.')
				return ull;


		}
	}
	return strtod(cp, pp);
}
