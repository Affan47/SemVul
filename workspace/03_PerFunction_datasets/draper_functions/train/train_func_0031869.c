fl_local_to_mac_roman(const char *t, int n)
{
  if (n==-1) n = strlen(t)+1;
  if (n>=n_buf) {
    n_buf = (n + 257) & 0x7fffff00;
    if (buf) free(buf);
    buf = (char*)malloc(n_buf);
  }
  const uchar *src = (const uchar*)t;
  uchar *dst = (uchar*)buf;
  for ( ; n>0; n--) {
    uchar c = *src;
    if (c>127)
      *dst++ = latin2roman[c-128];
    else
      *dst++ = c;
  }

  return buf;
}
