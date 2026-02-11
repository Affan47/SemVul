cbc_cost ( struct cipher_algorithm *cipher,
				size_t key_len,
				void ( * op ) ( struct cipher_algorithm *cipher,
						void *ctx, const void *src,
						void *dst, size_t len ) ) {
	static uint8_t random[8192];
	uint8_t key[key_len];
	uint8_t iv[cipher->blocksize];
	uint8_t ctx[cipher->ctxsize];
	union profiler profiler;
	unsigned long long elapsed;
	unsigned long cost;
	unsigned int i;
	int rc;


	srand ( 0x1234568 );
	for ( i = 0 ; i < sizeof ( random ) ; i++ )
		random[i] = rand();
	for ( i = 0 ; i < sizeof ( key ) ; i++ )
		key[i] = rand();
	for ( i = 0 ; i < sizeof ( iv ) ; i++ )
		iv[i] = rand();


	rc = cipher_setkey ( cipher, ctx, key, key_len );
	assert ( rc == 0 );
	cipher_setiv ( cipher, ctx, iv );


	profile ( &profiler );
	op ( cipher, ctx, random, random, sizeof ( random ) );
	elapsed = profile ( &profiler );


	cost = ( ( elapsed + ( sizeof ( random ) / 2 ) ) / sizeof ( random ) );

	return cost;
}
