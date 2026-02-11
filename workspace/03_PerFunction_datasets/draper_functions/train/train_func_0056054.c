white_aes( byte *out )
{
	u32 temp[AES_WORDS], white[AES_WORDS] ;
	u32 *p ;
	byte *t, *c ;


	t = (byte *) temp ;
	c = (byte *) counter ;

	chacha_copy( white, 1 ) ;
	memcpy( t, c, AES_BYTES ) ;
	add_128( temp, white ) ;


	(void) aes_encrypt( t, t, (byte *) aes_rk ) ;
	add_128( temp, white ) ;
	memcpy( out, t, AES_BYTES ) ;


	p = counter ;
	switch( iter_count )	{


		case 13:
			p[1] += p[2] ;
			break ;
		case 29:
			p[2] += p[3] ;
			break ;
		case 57:
			p[3] += p[1] ;
			break ;

		case 43:
			p[1] += p[0] ;
			break ;

		case 61:
			iter_count = -1 ;
			break ;
		default:
			break ;
	}


	p[0]++ ;
	iter_count++ ;
}
