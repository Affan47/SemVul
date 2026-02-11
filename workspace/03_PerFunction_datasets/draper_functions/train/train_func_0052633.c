bibtex_usestrings( newstr *s )
{
	int i;
	for ( i=0; i<find.n; ++i ) {
		if ( !strcasecmp( s->data, (find.str[i]).data ) ) {
			newstr_findreplace( s, (find.str[i]).data,
					(replace.str[i]).data );
			return 1;
		}
	}
	return 0;
}
