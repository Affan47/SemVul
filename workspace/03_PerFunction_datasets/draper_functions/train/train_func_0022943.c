crypto_digest_dup(const crypto_digest_t *digest)
{
  crypto_digest_t *r;
  tor_assert(digest);
  r = tor_malloc(sizeof(crypto_digest_t));
  memcpy(r,digest,sizeof(crypto_digest_t));
  return r;
}
