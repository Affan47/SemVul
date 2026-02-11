IsHexData(const char *str)
{
	for( int i = 0; i < 4 && *str; str++, i++ )
		if( *str != ' ' )
			return false;

	for( int i = 0; i < 8 && *str; str++, i++ )
		if( !isdigit(*str) && !(*str >= 'a' && *str <= 'f') )
			return false;

	if( *str != ':' )
		return false;

	return true;
}
