strip_comments (char *str)
{
	char *c = str;

	while (*c) {
		if (*c == '#') {
			*c = '\0';
			break;
		}

		c++;
	}

	return str;
}
