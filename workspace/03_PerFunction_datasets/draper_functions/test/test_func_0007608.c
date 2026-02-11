zx_url_encode(struct zx_ctx* c, int in_len, const char* in, int* out_len)
{
  int olen;
  char* out;
  char* p;
  if (in_len == -2)
    in_len = strlen(in);
  olen = zx_url_encode_len(in_len, in) + 1;
  out = ZX_ALLOC(c, olen);
  p = zx_url_encode_raw(in_len, in, out);
  *p = '\0';
  if (out_len)
    *out_len = p - out;
  return out;
}
