parseComment( void ) {
	gchar cCur = nextChar();

	if ( cCur != '/' ) {
		return 0;
	}

	while ( cCur != '\r' && cCur != '\n' && cCur ) {
		cCur = nextChar();
	}

	return 1;
}
