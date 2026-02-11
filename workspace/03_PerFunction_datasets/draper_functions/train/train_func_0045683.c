_checksum_64( SSLKey *key,
	const unsigned char *data, int dataLen, uint64_t *chainedIV)
{
    rAssert( dataLen > 0 );
    Lock lock( key->mutex );

    unsigned char md[EVP_MAX_MD_SIZE];
    unsigned int mdLen = EVP_MAX_MD_SIZE;

    HMAC_Init_ex( &key->mac_ctx, 0, 0, 0, 0 );
    HMAC_Update( &key->mac_ctx, data, dataLen );
    if(chainedIV)
    {

	uint64_t tmp = *chainedIV;
	unsigned char h[8];
	for(unsigned int i=0; i<8; ++i)
	{
	    h[i] = tmp & 0xff;
	    tmp >>= 8;
	}

	HMAC_Update( &key->mac_ctx, h, 8 );
    }

    HMAC_Final( &key->mac_ctx, md, &mdLen );

    rAssert(mdLen >= 8);


    unsigned char h[8] = {0,0,0,0,0,0,0,0};
    for(unsigned int i=0; i<(mdLen-1); ++i)
	h[i%8] ^= (unsigned char)(md[i]);

    uint64_t value = (uint64_t)h[0];
    for(int i=1; i<8; ++i)
	value = (value << 8) | (uint64_t)h[i];

    return value;
}
