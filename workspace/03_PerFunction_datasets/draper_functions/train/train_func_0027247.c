pine_clean_name( Pine_ParsedRec *rec ) {
	gchar *p;

	p = rec->name;
	if( p == NULL ) return;
	if( *p == '\0' ) return;

	g_strstrip( rec->name );
	if( *p == CHAR_APOS || *p == CHAR_QUOTE ) {
		return;
	}


	while( *p ) {
		if( *p == CHAR_COMMA ) {
			p = g_strdup_printf( "\"%s\"", rec->name );
			g_free( rec->name );
			rec->name = p;
			return;
		}
		p++;
	}
}
