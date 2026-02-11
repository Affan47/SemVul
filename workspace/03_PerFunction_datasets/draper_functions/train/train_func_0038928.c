dsa_sign_hash(const unsigned char *in,  unsigned long inlen,
                        unsigned char *out, unsigned long *outlen,
                        prng_state *prng, int wprng, dsa_key *key)
{
   void         *r, *s;
   int           err;

   LTC_ARGCHK(in      != NULL);
   LTC_ARGCHK(out     != NULL);
   LTC_ARGCHK(outlen  != NULL);
   LTC_ARGCHK(key     != NULL);

   if (mp_init_multi(&r, &s, NULL) != CRYPT_OK) {
      return CRYPT_MEM;
   }

   if ((err = dsa_sign_hash_raw(in, inlen, r, s, prng, wprng, key)) != CRYPT_OK) {
      goto LBL_ERR;
   }

   err = der_encode_sequence_multi(out, outlen,
                             LTC_ASN1_INTEGER, 1UL, r,
                             LTC_ASN1_INTEGER, 1UL, s,
                             LTC_ASN1_EOL,     0UL, NULL);

LBL_ERR:
   mp_clear_multi(r, s, NULL);
   return err;
}
