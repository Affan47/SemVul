rinkj_escp_1pass_dblx (char *dst, const char *src, int n_bytes)
{
  int i;


  for (i = 0; i < n_bytes; i ++)
    {
      unsigned char s = src[i];
      dst[i * 2] = (((s & 0x80) >> 1) | ((s & 0x40) >> 2) |
                    ((s & 0x20) >> 3) | ((s & 0x10) >> 4)) * DOT;
      dst[i * 2 + 1] = (((s & 8) << 3) | ((s & 4) << 2) |
                    ((s & 2) << 1) | (s & 1)) * DOT;
    }
}
