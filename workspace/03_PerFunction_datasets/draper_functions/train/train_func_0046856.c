crypto_aead_encrypt(
	unsigned char *c,unsigned long long *clen,
	const unsigned char *m,unsigned long long mlen,
	const unsigned char *ad,unsigned long long adlen,
	const unsigned char *nsec,
	const unsigned char *npub,
	const unsigned char *k
	)
{
        unsigned long i;
        unsigned char plaintextblock[32], ciphertextblock[32], mac[16];
        unsigned char aegis128L_state[128];


        aegis128L_initialization(k, npub, aegis128L_state);


        for (i = 0; (i+32) <= adlen; i += 32) {
              aegis128L_enc_aut_step(ad+i, ciphertextblock, aegis128L_state);
        }


        if (  (adlen & 0x1f) != 0 )  {
              memset(plaintextblock, 0, 32);
              memcpy(plaintextblock, ad+i, adlen & 0x1f);
              aegis128L_enc_aut_step(plaintextblock, ciphertextblock, aegis128L_state);
        }


        for (i = 0; (i+32) <= mlen; i += 32) {
              aegis128L_enc_aut_step(m+i, c+i, aegis128L_state);
        }


        if (  (mlen & 0x1f) != 0 )  {
              memset(plaintextblock, 0, 32);
              memcpy(plaintextblock, m+i, mlen & 0x1f);
              aegis128L_enc_aut_step(plaintextblock, ciphertextblock, aegis128L_state);
              memcpy(c+i,ciphertextblock, mlen & 0x1f);
        }


        aegis128L_tag_generation(mlen, adlen, 16, mac, aegis128L_state);
        *clen = mlen + 16;
        memcpy(c+mlen, mac, 16);

        return 0;
}
