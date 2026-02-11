get_token(char **str) {
	char *p, *retval;
	if (!*str || !*str[0])
		return NULL;
	p = strchr(*str, (int)'_');
	if (!p) {
		p = strchr(*str, (int)'\0');
		if(!p) return NULL;
		retval = strdup(*str);
		*str = p;
	} else {
		retval = (char*)substrdup(*str, p - *str);
		*str = p + 1;
	}
	return retval;
}
