sh_quote(text)
char *text ;
{

    char *tmp = check_malloc(strlen(text) * 2) ;


    char *ptr = tmp ;


    while (*text != '\0') {
	if (*text == '\\' || *text == '$' || *text == '\"') {

	    *ptr++ = '\\' ;
	}
	*ptr++ = *text++ ;
    }
    *ptr = '\0' ;
    tmp = check_realloc(tmp, strlen(tmp) + 1) ;

    return tmp ;
}
