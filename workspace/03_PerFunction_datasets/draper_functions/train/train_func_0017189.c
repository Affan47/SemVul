crypto_aead_encrypt(
		unsigned char *c, unsigned long long *clen,
		const unsigned char *m, unsigned long long mlen,
		const unsigned char *ad, unsigned long long adlen,
		const unsigned char *nsec,
		const unsigned char *npub,
		const unsigned char *k
		)
{

    *clen = mlen + CRYPTO_ABYTES;

    unsigned char tag[CRYPTO_ABYTES];
    ae_cxt* cxt = ae_allocate();
    if(!cxt)
        return RETURN_MEMORY_FAIL;


    if(ae_init(cxt, k, CRYPTO_KEYBYTES))
        return RETURN_KEYSIZE_ERR;


    process_ad(cxt, ad, adlen, npub, CRYPTO_NPUBBYTES);


    ae_encrypt(cxt, (unsigned char*)m, mlen, c, tag, CRYPTO_ABYTES, ENC);


    memcpy(c+mlen, tag, CRYPTO_ABYTES);
	return RETURN_SUCCESS;
}
