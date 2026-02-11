fortuna_read(unsigned char *out, unsigned long outlen, prng_state *prng)
{
   unsigned char tmp[16];
   int           err;
   unsigned long tlen;

   LTC_ARGCHK(out  != NULL);
   LTC_ARGCHK(prng != NULL);

   LTC_MUTEX_LOCK(&prng->fortuna.prng_lock);


   if (++prng->fortuna.wd == FORTUNA_WD || prng->fortuna.pool0_len >= 64) {
      if ((err = fortuna_reseed(prng)) != CRYPT_OK) {
         LTC_MUTEX_UNLOCK(&prng->fortuna.prng_lock);
         return 0;
      }
   }


   tlen = outlen;


   while (outlen >= 16) {

      rijndael_ecb_encrypt(prng->fortuna.IV, out, &prng->fortuna.skey);
      out += 16;
      outlen -= 16;
      fortuna_update_iv(prng);
   }


   if (outlen > 0) {
      rijndael_ecb_encrypt(prng->fortuna.IV, tmp, &prng->fortuna.skey);
      XMEMCPY(out, tmp, outlen);
      fortuna_update_iv(prng);
   }


   rijndael_ecb_encrypt(prng->fortuna.IV, prng->fortuna.K   , &prng->fortuna.skey); fortuna_update_iv(prng);
   rijndael_ecb_encrypt(prng->fortuna.IV, prng->fortuna.K+16, &prng->fortuna.skey); fortuna_update_iv(prng);
   if ((err = rijndael_setup(prng->fortuna.K, 32, 0, &prng->fortuna.skey)) != CRYPT_OK) {
      LTC_MUTEX_UNLOCK(&prng->fortuna.prng_lock);
      return 0;
   }

#ifdef LTC_CLEAN_STACK
   zeromem(tmp, sizeof(tmp));
#endif
   LTC_MUTEX_UNLOCK(&prng->fortuna.prng_lock);
   return tlen;
}
