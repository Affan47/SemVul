crypto_aead_encrypt(
	unsigned char *c,unsigned long long *clen,
	const unsigned char *m,unsigned long long mlen,
	const unsigned char *ad,unsigned long long adlen,
	const unsigned char *nsec,
	const unsigned char *npub,
	const unsigned char *k )
{
    ICESTATE S;
    unsigned int frameBit;
    initState256a(S, k, npub);


    *clen = mlen + ICEPOLETAGLEN;


    frameBit = 0;
    processIceBlock(S, NULL, NULL, 0, frameBit);


    do {
        unsigned long long blocklen = 128;
        frameBit = (adlen <= blocklen ? 1 : 0);
        if (adlen < blocklen) {
            blocklen = adlen;
        }
        processIceBlock(S, ad, NULL, blocklen, frameBit);
        ad += blocklen;
        adlen -= blocklen;
    } while (adlen > 0);


    do {
        unsigned long long blocklen = 128;
        frameBit = (mlen <=blocklen ? 0 : 1);
        if (mlen < blocklen) {
            blocklen = mlen;
        }
        processIceBlock(S, m, &c, blocklen, frameBit);
        m += blocklen;
        mlen -= blocklen;
    } while (mlen > 0);


    store64(c, S[0][0], 8);
    c += 8;
    store64(c, S[1][0], 8);

    return 0;
}
