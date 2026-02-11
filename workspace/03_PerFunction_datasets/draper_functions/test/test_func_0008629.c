crcitt_string( char *s, int len )
{
	register unsigned short ccitt;

	ccitt = 0xFFFF;

	while( len ) {
		ccitt = UPDCIT(*s, ccitt);
		s++; len--;
	}
	return ~ccitt;
}
