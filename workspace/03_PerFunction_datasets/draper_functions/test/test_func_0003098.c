edsign_sign(const uint8_t* pass, const uint64_t passlen,
            const uint8_t* sk,
            const uint8_t* msg, const uint64_t msglen,
            uint8_t* out)
{
  uint32_t N, r, p;
  uint8_t* pp;
  uint8_t* pout;
  uint8_t* salt;
  uint8_t* digest;
  uint8_t* fp;
  uint8_t* enckey;
  uint8_t key[crypto_sign_ed25519_SECRETKEYBYTES];
  uint8_t hash[crypto_hash_blake2b_BYTES];
  uint8_t sig[crypto_hash_blake2b_BYTES + crypto_sign_ed25519_BYTES];
  uint64_t siglen;
  uint64_t i;
  int res = EDSIGN_ERROR;


  if (msg == NULL) return EDSIGN_EINVAL;
  if (out == NULL) return EDSIGN_EINVAL;
  if (sk  == NULL) return EDSIGN_EINVAL;

  pp = (uint8_t*)sk;


  if (0 != edsign_memcmp(pp, (uint8_t*)PKALG, 2)) return EDSIGN_EINVAL;
  pp += 2;

  if (0 != edsign_memcmp(pp, (uint8_t*)KDFALG, 2)) return EDSIGN_EINVAL;
  pp += 2;


  N = edsign_le32dec(pp); pp += 4;
  r = edsign_le32dec(pp); pp += 4;
  p = edsign_le32dec(pp); pp += 4;


  salt   = pp; pp += 16;
  digest = pp; pp += 8;
  fp     = pp; pp += 8;
  enckey = pp;


  if (pass != NULL) {
    uint64_t pow2N = ((uint64_t)1) << N;
    res = crypto_scrypt(pass, passlen, salt, 16, pow2N, r, p,
                        key, sizeof(key));
    if (res != 0) {
      res = EDSIGN_EINVAL;
      goto exit;
    }
  }
  else {

    edsign_bzero(key, sizeof(key));
  }


  for (i = 0; i < sizeof(key); ++i) key[i] ^= enckey[i];


  crypto_hash_blake2b(hash, key, sizeof(key));
  if (0 != edsign_memcmp(hash, digest, 8)) {
    res = EDSIGN_EPASSWD;
    goto exit;
  }


  crypto_hash_blake2b(hash, msg, msglen);


  crypto_sign_ed25519(sig, &siglen, hash, sizeof(hash), key);
  assert(siglen == sizeof(sig));


  pout = out;
  memcpy(pout, PKALG, 2); pout += 2;
  memcpy(pout, fp, 8);    pout += 8;
  memcpy(pout, sig, 64);

  edsign_bzero(sig, sizeof(sig));
  res = EDSIGN_OK;
 exit:
  edsign_bzero(key, sizeof(key));
  edsign_bzero(hash, sizeof(hash));
  return res;
}
