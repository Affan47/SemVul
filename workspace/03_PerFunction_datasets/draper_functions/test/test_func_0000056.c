quote_clean(char *rawline)
{
    char *p, *q, *cleaned = NULL;
    size_t len;

    if(rawline){
	len = strlen(rawline);
	cleaned = (char *) malloc((2*len+1) * sizeof(char));

	if(cleaned){
	    p = rawline;
	    q = cleaned;

	    while(*p && *p != '\n'){
		if(*p == '"' && !(p > rawline && *(p-1) == '\\'))
		  *q++ = '\\';

		*q++ = *p++;
	    }

	    *q = '\0';
	}
    }

    return cleaned;
}
