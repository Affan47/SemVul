isValidChineseString( char *str )
{
	if ( strlen( str ) == 0 ) {
		return  0;
	}
	while ( *str != '\0' )  {
		int len = ueBytesFromChar( (unsigned char) *str );
		if ( len <= 1 ) {
			return 0;
		}
		str += len;
	};
	return 1;
}
