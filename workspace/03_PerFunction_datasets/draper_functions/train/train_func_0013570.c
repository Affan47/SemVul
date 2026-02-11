zxid_mk_id(zxid_conf* cf, char* prefix, int bits)
{
  char bit_buf[ZXID_ID_MAX_BITS/8];
  char base64_buf[ZXID_ID_MAX_BITS/6 + 1];
  char* p;
  if (bits > ZXID_ID_MAX_BITS || bits & 0x07) {
    ERR("Requested bits(%d) more than internal limit(%d), or bits not divisible by 8.", bits, ZXID_ID_MAX_BITS);
    return 0;
  }
  zx_rand(bit_buf, bits >> 3);
  p = base64_fancy_raw(bit_buf, bits >> 3, base64_buf, safe_basis_64, 1<<31, 0, 0, '.');
  return zx_strf(cf->ctx, "%s%.*s", prefix?prefix:"", p-base64_buf, base64_buf);
}
