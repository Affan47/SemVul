twofish_setkey (void *context, const byte *key, unsigned int keylen)
{
  TWOFISH_context *ctx = context;
  int rc = do_twofish_setkey (ctx, key, keylen);
  _gcry_burn_stack (23+6*sizeof(void*));
  return rc;
}
