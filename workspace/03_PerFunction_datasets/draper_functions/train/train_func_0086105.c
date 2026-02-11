CompRecord( const void *a, const void *b )
{
	long i;
	int cmp;

	for ( i = 0; i < MAXZUIN; i++ ) {
		cmp = ((RECORD *) a)->num[ i ] - ((RECORD *) b)->num[ i ];
		if ( cmp )
			return cmp;
	}
	return ( ((RECORD *) b)->freq - ((RECORD *) a)->freq );
}
