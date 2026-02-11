UsedIn(char *name, char *subs) {
    int nlen = strlen( name );
    while ( *subs!='\0' ) {
	if ( strncmp(subs,name,nlen)==0 && (subs[nlen]==' ' || subs[nlen]=='\0'))
return( true );
	while ( *subs!=' ' && *subs!='\0' ) ++subs;
	while ( *subs==' ' ) ++subs;
    }
return( false );
}
