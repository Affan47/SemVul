crypto_aead_decrypt(
	unsigned char *m,unsigned long long *mlen,
	unsigned char *nsec,
	const unsigned char *c,unsigned long long clen,
	const unsigned char *ad,unsigned long long adlen,
	const unsigned char *npub,
	const unsigned char *k
	)
{
    unsigned long i;
    unsigned char plaintextbyte, ciphertextbyte, ksbyte;
    unsigned char state[293];
    unsigned char tag[16];
    unsigned char check = 0;
    unsigned char ca, cb;

    if (clen < 16) return -1;


    acorn128_initialization(k, npub, state);


    for (i = 0; i < adlen; i++)
    {
        acorn128_enc_onebyte(state, ad[i], &ciphertextbyte, &ksbyte, 0xff, 0xff);
    }

    for (i = 0; i < 512/8; i++)
    {
        if ( i == 0 ) plaintextbyte = 1;
        else plaintextbyte = 0;

        if ( i < 256/8)   ca = 0xff;
        else ca = 0;

        cb = 0xff;

        acorn128_enc_onebyte(state, plaintextbyte, &ciphertextbyte, &ksbyte, ca, cb);
    }


    *mlen = clen - 16;

    for (i = 0; i < *mlen; i++)
    {
        acorn128_dec_onebyte(state, &m[i], c[i], &ksbyte, 0xff, 0 );
    }

    for (i = 0; i < 512/8; i++)
    {
        if ( i == 0 ) plaintextbyte = 1;
        else plaintextbyte = 0;

        if ( i < 256/8)   ca = 0xff;
        else ca = 0;

        cb = 0;

        acorn128_enc_onebyte(state, plaintextbyte, &ciphertextbyte, &ksbyte, ca, cb);
    }


    acorn128_tag_generation(*mlen, adlen, 16, tag, state);

    for (i = 0; i  < 16; i++) check |= (tag[i] ^ c[clen - 16 + i]);
    if (check == 0) return 0;
    else return -1;
}
