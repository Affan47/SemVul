seedMT( unsigned int seed, unsigned int *state, unsigned int *&next, int &left )
{
	(void) next;


	register unsigned int x = ( seed | 1U ) & 0xFFFFFFFFU, *s = state;
	register int j;

	for ( left = 0, *s++ = x, j = N; --j;
		*s++ = ( x *= 69069U ) & 0xFFFFFFFFU )

		;
}
