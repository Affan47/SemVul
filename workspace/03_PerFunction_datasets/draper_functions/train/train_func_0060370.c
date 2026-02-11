edsign_keypair(const uint8_t* pass, const uint64_t passlen,
               const uint32_t N, const uint32_t r, const uint32_t p,
               uint8_t* pkout, uint8_t* skout)
{
  uint8_t pk[crypto_sign_ed25519_PUBLICKEYBYTES];
  uint8_t sk[crypto_sign_ed25519_SECRETKEYBYTES];
  uint8_t digest[crypto_hash_blake2b_BYTES];
  uint8_t fingerprint[8];
  uint8_t salt[16];
  uint8_t* pp;
  uint64_t i;
  int res = EDSIGN_ERROR;

  if (pkout == NULL) return EDSIGN_EINVAL;
  if (skout == NULL) return EDSIGN_EINVAL;

  edsign_randombytes(salt, sizeof(salt));
  edsign_randombytes(fingerprint, sizeof(fingerprint));
  crypto_sign_ed25519_keypair(pk, sk);
  crypto_hash_blake2b(digest, sk, sizeof(sk));


  pp = pkout;
  memcpy(pp, PKALG, 2); pp += 2;
  memcpy(pp, fingerprint, sizeof(fingerprint)); pp += sizeof(fingerprint);
  memcpy(pp, pk, crypto_sign_ed25519_PUBLICKEYBYTES);


  pp = skout;
  memcpy(pp, PKALG, 2);  pp += 2;
  memcpy(pp, KDFALG, 2); pp += 2;

  edsign_le32enc(pp, (pass == NULL) ? 0 : N); pp += 4;
  edsign_le32enc(pp, (pass == NULL) ? 0 : r); pp += 4;
  edsign_le32enc(pp, (pass == NULL) ? 0 : p); pp += 4;
  memcpy(pp, salt, sizeof(salt)); pp += sizeof(salt);
  memcpy(pp, digest, 8); pp += 8;
  memcpy(pp, fingerprint, sizeof(fingerprint)); pp += sizeof(fingerprint);

  edsign_bzero(digest, sizeof(digest));


  if (pass != NULL) {
    uint64_t pow2N = ((uint64_t)1) << N;
    res = crypto_scrypt(pass, passlen, salt, sizeof(salt), pow2N, r, p,
                        pp, crypto_sign_ed25519_SECRETKEYBYTES);

    if (res != 0) {
      res = EDSIGN_EINVAL;
      edsign_bzero(pkout, edsign_PUBLICKEYBYTES);
      edsign_bzero(skout, edsign_SECRETKEYBYTES);
      goto exit;
    }
  }
  else {
    edsign_bzero(pp, crypto_sign_ed25519_SECRETKEYBYTES);
  }


  for (i = 0; i < sizeof(sk); ++i) pp[i] ^= sk[i];
  res = EDSIGN_OK;
 exit:
  edsign_bzero(sk, sizeof(sk));
  return res;
}
