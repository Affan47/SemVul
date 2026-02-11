getnum(char *s, char **e)
{
	int ret = -1;

	*e = (char *) 0;
	ret = strtol(s, e, 0);
	if (*e)
		switch (**e) {
		case 'b':
		case 'B':
			ret *= 512;
			*e = *e + 1;
			break;
		case 'k':
		case 'K':
			ret *= 1024;
			*e = *e + 1;
			break;
		case 'm':
		case 'M':
			ret *= 1024*1024;
			*e = *e + 1;
			break;
		case 'w':
		case 'W':
			ret *= 4;
			*e = *e + 1;
			break;
		}
	return (ret);
}
