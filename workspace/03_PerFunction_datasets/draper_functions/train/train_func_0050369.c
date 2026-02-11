bibtex_cleandata( newstr *s, fields *info, param *p )
{
	list tokens;
	int i;
	if ( !s->len ) return;
	list_init( &tokens );
	bibtex_split( &tokens, s );
	for ( i=0; i<tokens.n; ++i ) {
		if ( !bibtex_protected( &(tokens.str[i] ) ) ) {
			bibtex_usestrings( &(tokens.str[i]) );
		} else {
			if (!strncasecmp(tokens.str[i].data,"\\href{", 6)) {
				bibtex_addtitleurl( info, &(tokens.str[i]) );
			}
			bibtex_cleantoken( &(tokens.str[i]), p );
		}
	}
	newstr_empty( s );
	for ( i=0; i<tokens.n; ++i ) {
		if ( bibtex_protected( &(tokens.str[i]) ) )
			bibtex_removeprotection( &(tokens.str[i]));
		newstr_strcat( s, tokens.str[i].data );
	}
	list_free( &tokens );
}
