edsign_verify(const uint8_t* pk, const uint8_t *sig,
              const uint8_t* msg,  const uint64_t msglen)
{
  int res = EDSIGN_ERROR;
  uint64_t tlen;
  uint8_t hash[crypto_hash_blake2b_BYTES];
  uint8_t smsg[crypto_hash_blake2b_BYTES + crypto_sign_ed25519_BYTES];
  uint8_t out[crypto_hash_blake2b_BYTES + crypto_sign_ed25519_BYTES];

  if (pk  == NULL) return EDSIGN_EINVAL;
  if (sig == NULL) return EDSIGN_EINVAL;
  if (msg == NULL) return EDSIGN_EINVAL;

  if (0 != edsign_memcmp(pk, (uint8_t*)PKALG, 2)) return EDSIGN_EINVAL;
  if (0 != edsign_memcmp(sig, (uint8_t*)PKALG, 2)) return EDSIGN_EINVAL;
  if (0 != edsign_memcmp(pk+2, sig+2, 8)) return EDSIGN_EKEY;


  crypto_hash_blake2b(hash, msg, msglen);
  memcpy(smsg,    sig+10, 64);
  memcpy(smsg+64, hash, sizeof(hash));


  res = crypto_sign_open(out, &tlen, smsg, sizeof(smsg), pk+10);
  assert(tlen == crypto_hash_blake2b_BYTES);
  if (res != 0) res = EDSIGN_ESIG;
  return res;
}
