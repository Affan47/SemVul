localeptsize(void) {
    const char *loc = getenv("LC_ALL");
    if ( loc==NULL ) loc = getenv("LC_CTYPE");
    if ( loc==NULL ) loc = getenv("LANG");

    if ( loc==NULL )
return( -10 );
    else if ( strncmp(loc,"ja",2)==0 ||
		strncmp(loc,"zh",2)==0 ||
		strncmp(loc,"ko",2)==0 )
return( -16 );

return( -10 );
}
