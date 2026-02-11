parse_timeout(const char *arg)
{
	unsigned int	v, ret = 0;
	char		*s;

	do {
		v = strtoul(arg, &s, 10);
		switch (*s) {
		case '\0':
			ret += v;
			break;
		case 'd':
			v *= 24;
		case 'h':
			v *= 60;
		case 'm':
			v *= 60;
		case 's':
			ret += v;
			++s;
			break;

		default:
			errx(1, "parse_timeout: unexpected character in \"%s\"\n",
					arg);
		}

		arg = s;
	} while (*arg);

	return ret;
}
