cmp_votes( const void *bs1, const void *bs2 )
{
	if( ((vote *) bs1)->val < ((vote *) bs2)->val )
		return(  1 );

	if( ((vote *) bs1)->val > ((vote *) bs2)->val )
		return( -1 );

	return( 0 );
}
