rend_get_service_id(crypto_pk_t *pk, char *out)
{
  char buf[DIGEST_LEN];
  tor_assert(pk);
  if (crypto_pk_get_digest(pk, buf) < 0)
    return -1;
  base32_encode(out, REND_SERVICE_ID_LEN_BASE32+1, buf, REND_SERVICE_ID_LEN);
  return 0;
}
