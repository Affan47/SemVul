base64_encode ( const uint8_t *raw, size_t len, char *encoded ) {
	const uint8_t *raw_bytes = ( ( const uint8_t * ) raw );
	uint8_t *encoded_bytes = ( ( uint8_t * ) encoded );
	size_t raw_bit_len = ( 8 * len );
	unsigned int bit;
	unsigned int byte;
	unsigned int shift;
	unsigned int tmp;

	for ( bit = 0 ; bit < raw_bit_len ; bit += 6 ) {
		byte = ( bit / 8 );
		shift = ( bit % 8 );
		tmp = ( raw_bytes[byte] << shift );
		if ( ( byte + 1 ) < len )
			tmp |= ( raw_bytes[ byte + 1 ] >> ( 8 - shift ) );
		tmp = ( ( tmp >> 2 ) & 0x3f );
		*(encoded_bytes++) = base64[tmp];
	}
	for ( ; ( bit % 8 ) != 0 ; bit += 6 )
		*(encoded_bytes++) = '=';
	*(encoded_bytes++) = '\0';

	DBG ( "Base64-encoded to \"%s\":\n", encoded );
	DBG_HDA ( 0, raw, len );
	assert ( strlen ( encoded ) == base64_encoded_len ( len ) );
}
