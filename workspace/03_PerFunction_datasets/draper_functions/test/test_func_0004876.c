fdelimtok(char *delims, FILE *file, int flags)
{
	static char *token = NULL;
	static int troom = 0;
	int c;
	char *p;
	char *q;
	int term;

	if((term = fnextc(file, flags)) == EOF)
	    return NULL;

	if(token == NULL) {
	    troom = 50;
	    token = malloc(troom * sizeof(char));
	    if(token == NULL)
		return NULL;
	}

	p = token;
	switch(term) {
	case '"':
	case '\'':
	    (void) fgetc(file);
	    for(;;) {
		if((c = getc(file)) == EOF || c == term)
		    break;
		else if(c == '\\')
		    c = fescape(file);
		*p++ = c;
		if(p == &token[troom]) {
		    token = realloc(token, troom * 2);
		    if(token == NULL)
			return NULL;
		    p = &token[troom];
		    troom *= 2;
		}
	    }
	    break;

	default:
	    if(isspace(term))
		return NULL;
	    while((c = getc(file)) != EOF && !isspace(c)) {
		if(c == '\\')
		    c = fescape(file);
		*p = c;
		if(++p == &token[troom]) {
		    token = realloc(token, troom * 2);
		    if(token == NULL)
			return NULL;
		    p = &token[troom];
		    troom *= 2;
		}
		for(q = delims; *q && c != *q; q++)
		    ;
		if(*q) {
		    if(p > token+1) {
			p--;
			ungetc(c, file);
		    }
		    break;
		}
	    }
	    break;
	}
	*p = '\0';
	return token;
}
