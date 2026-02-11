strrstr(char *s1,char *s2)
{
    char *sc2 = NULL , *psc1 = NULL , *ps1 = NULL ;

    if ( *s2 == '\0' ) { return s1; }
    ps1 = s1 + strlen(s1);

    while( ps1 != s1 ) {
	--ps1;
	for ( psc1 = ps1, sc2 = s2; ; ) {
	    if (*(psc1++) != *(sc2++)) { break; }
	    else if ( *sc2 == '\0' ) { return ps1; }
	}
    }
    return NULL;
}
