randomMT( unsigned int *state, unsigned int *&next, int &left )
{
	unsigned int y;

	if ( --left < 0 )
		return ( reloadMT(state, next, left) );

	y = *next++;

	y ^= ( y >> 11 );

	y ^= ( y << 7 ) & 0x9D2C5680U;

	y ^= ( y << 15 ) & 0xEFC60000U;

	return ( y ^ ( y >> 18 ) );


}
