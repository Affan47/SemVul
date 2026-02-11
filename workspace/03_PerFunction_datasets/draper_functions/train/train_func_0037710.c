get_token_from_line(char **ptr)
{
	char *tok, *cp = *ptr;

	while (*cp == ' ' || *cp == '\t') cp++;

	if (*cp == 0) {
		*ptr = cp;
		return NULL;
	}

	tok = cp;

	while (*cp != 0 && *cp != ' ' && *cp != '\t') {

		if (*cp == '\\') {
			char *tp;
			for (tp = cp; tp != tok; tp--)
				*tp = *(tp-1);
			cp++;
			tok++;
			if (*cp == 0)
				break;
		}
		cp++;
	}
	if (*cp)
		*cp++ = 0;
	*ptr = cp;
	return tok;
}
