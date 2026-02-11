parseRow( int nTableId, int nTableScope ) {
	gchar bResult = 1;
	gchar cCur = nextChar();
	GString *psText = g_string_new( NULL );
	int nId, nScope;

	nMorkNowParsing = PARSE_ROWS;

	while ( cCur != '(' && cCur != ']' && cCur != '[' && cCur ) {
		if ( !isWhiteSpace( cCur ) ) {
			psText = g_string_append_c( psText, cCur );
		}
		cCur = nextChar();
	}

	parseScopeId( psText, &nId, &nScope );
	setCurrentRow( nTableScope, nTableId, nScope, nId );

	while ( bResult && cCur != ']' && cCur ) {
		if ( !isWhiteSpace( cCur ) ) {
			switch ( cCur ) {
				case '(':
					bResult = parseCell();
					break;
				case '[':
					bResult = parseMeta( ']' );
					break;
				default:
					bResult = 0;
					break;
			}
		}
		cCur = nextChar();
	}

	g_string_free( psText, TRUE );

	return bResult;
}
