strip_blanks(char *s)
{
    char *t;
    for( t=s; *s != '\0'; s++ ) {
	if( !isspace(*s) )
	    *t++ = *s;
    }
    *t = '\0';
}
