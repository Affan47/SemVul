tokenize(char **result, size_t reslen, char *str, char delim) {
	char *p = NULL, *n = NULL;
	size_t i;

	if(!str)
		return 0;
	for(n = str; *n == ' '; n++);
	p = n;
	for(i = 0; *n != 0;) {
		if(i == reslen)
			return 0;
		if(i > TOK_CHAN - TOK_CMD && strtol(result[0], NULL, 10) > 0) delim=':';
		if(*n == delim) {
			*n = 0;
			result[i++] = p;
			p = ++n;
		} else
			n++;
	}
	if(i<reslen && p < n && strlen(p))
		result[i++] = p;
	return i;
}
