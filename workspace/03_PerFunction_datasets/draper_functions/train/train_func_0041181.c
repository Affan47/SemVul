strmember( char *s, char *e )
#else
strmember( s, e )
char *s;
char *e;
#endif
{
    register char *p;
    require(s!=NULL&&e!=NULL, "strmember: NULL string");

    if ( *e=='\0' ) return 1;
    do {
	while ( *s!='\0' && !isalnum(*s) && *s!='_' )
	++s;
	p = e;
	while ( *p!='\0' && *p==*s ) {p++; s++;}
	if ( *p=='\0' ) {
	    if ( *s=='\0' ) return 1;
	    if ( !isalnum (*s) && *s != '_' ) return 1;
	}
	while ( isalnum(*s) || *s == '_' )
	++s;
    } while ( *s!='\0' );
    return 0;
}
