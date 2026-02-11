mycmp(char *str,char *within, char *end ) {
    while ( within<end ) {
	if ( *str!=*within )
return( *str-*within );
	++str; ++within;
    }
return( *str=='\0'?0:1 );
}
