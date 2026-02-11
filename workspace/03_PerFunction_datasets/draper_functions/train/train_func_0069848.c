LexerInput( char* buf, int max_size )
#endif
{
	if ( yyin->eof() || yyin->fail() )
		return 0;

#ifdef YY_INTERACTIVE
	yyin->get( buf[0] );

	if ( yyin->eof() )
		return 0;

	if ( yyin->bad() )
		return -1;

	return 1;

#else
	(void) yyin->read( buf, max_size );

	if ( yyin->bad() )
		return -1;
	else
		return yyin->gcount();
#endif
}
