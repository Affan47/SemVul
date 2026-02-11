crypto_aead_encrypt(
			unsigned char *c,unsigned long long *clen,
			const unsigned char *m,unsigned long long mlen,
			const unsigned char *ad,unsigned long long adlen,
			const unsigned char *nsec,
			const unsigned char *npub,
			const unsigned char *k
			) {
   (void)nsec;

   int res = omdsha256_process(c, k, m, mlen, ad, adlen, npub, OMD_ENCRYPT);

   if (res != -1)
      *clen = mlen + CRYPTO_ABYTES;

   return res;
}
