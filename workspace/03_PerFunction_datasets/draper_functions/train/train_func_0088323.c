SWAP(md5_uint32 n)
{
  static int checked = 0;
  static int bigendian = 0;
  static md5_uint32 test;

  if (!checked) {
    test = 1;
    if (* (char *) &test == 0)
      bigendian = 1;
    checked = 1;
  }

  if (bigendian)
    return (((n) << 24) | (((n) & 0xff00) << 8) | (((n) >> 8) & 0xff00) | ((n) >> 24));
  else
    return n;
}
