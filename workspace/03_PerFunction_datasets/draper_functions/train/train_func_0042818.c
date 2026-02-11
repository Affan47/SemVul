chacha_copy( u32 *dest, u32 blocks )
{
	u32 i ;

	assert( dest != NULL ) ;
	assert( chacha_got <= 4 ) ;

	for( i = blocks ; i > 0 ; i-- )	{
		if( chacha_got == 0 )	{
			chacha_round() ;
		}
		memcpy( dest, chacha_next, AES_BYTES ) ;
		dest += AES_WORDS ;
		chacha_next += AES_WORDS ;
		chacha_got-- ;
	}
}
