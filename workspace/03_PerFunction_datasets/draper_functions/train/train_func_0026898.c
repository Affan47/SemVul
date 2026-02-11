checksum( char *sum, const char * key, const char * buf )
{
	uint32_t crc = 0;
	uint32_t lword, irword;
	int idx, buf_len = strlen(buf);
	uint32_t seed = (uint32_t) strtoul( key, NULL, 0 );

	for ( idx = 0; idx < buf_len; ++idx ) {
		crc = (uint32_t) compute_crc( crc, buf[idx] );
	}

	lword = crc;
	irword = seed;

	des( &lword, &irword );

	sprintf(sum, "CK=%08x%08x", lword, irword);
}
