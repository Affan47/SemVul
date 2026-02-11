strtoken(char *src)
{
	static char *buf = NULL, *vptr;
	char *retptr;

	if (src) {
		if (buf) free(buf);
		buf = safe_strdup(src);
		vptr = buf;
	} else if (buf == NULL) {
		fprintf(stderr, "illegal strtoken call\n");
		exit(1);
	}


	while (*vptr && strchr(DELIM, *vptr))
		vptr++;
	if (!*vptr)
		return NULL;

	retptr = vptr;
	while (*vptr && strchr(DELIM, *vptr) == NULL) {
		if (*vptr == '\\') {
			remove_letter(vptr);
			if (!*vptr)
				break;
			vptr++;
		} else if (*vptr == '"' || *vptr == '\'') {
			int prev, quote;
			prev = quote = *vptr;
			remove_letter(vptr);
			for (; *vptr; prev = *vptr, vptr++) {
				if (*vptr == '\\') {
					remove_letter(vptr);
					if (*vptr)
						break;
				} else if (*vptr == quote) {
					remove_letter(vptr);
					break;
				}
			}
		} else
			vptr++;
	}
	if (*vptr)
		*vptr++ = 0;
	return retptr;
}
