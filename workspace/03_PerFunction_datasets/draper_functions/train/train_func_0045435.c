encode_basic (punycode_uint bcp, int flag)
{
  bcp -= (bcp - 97 < 26) << 5;
  return bcp + ((!flag && (bcp - 65 < 26)) << 5);
}
