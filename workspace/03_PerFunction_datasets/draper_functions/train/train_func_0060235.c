unw_decode_r3 (const unsigned char *dp, unsigned int code, void *arg)
{
  unw_word rlen;

  rlen = unw_decode_uleb128 (& dp);
  UNW_DEC_PROLOGUE ("R3", ((code & 0x3) == 1), rlen, arg);
  return dp;
}
