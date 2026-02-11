hmacsha256_init(gcry_md_hd_t *mh, const char *key, int len)
{
  gcry_error_t err;

  err = gcry_md_open(mh, GCRY_MD_SHA256,
		     GCRY_MD_FLAG_HMAC | GCRY_MD_FLAG_SECURE);
  if (gcry_err_code(err))
    return 0;

  err = gcry_md_setkey(*mh, key, len);
  return ! gcry_err_code(err);
}
