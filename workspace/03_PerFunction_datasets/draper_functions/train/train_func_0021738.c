PhoneSeqTheSame( const uint16_t p1[], const uint16_t p2[] )
{
	int i;
	if ( ! p1 || ! p2 )
		return 0;

	for ( i = 0; ( p1[ i ] != 0 && p2[ i ] != 0 ); i++ ) {
		if ( p1[ i ] != p2[ i ] )
			return 0;
	}
	if ( p1[ i ] != p2[ i ] )
		return 0;
	return 1;
}
