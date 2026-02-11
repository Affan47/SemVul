utf8toa(const char* src, unsigned srclen,
                        char* dst, unsigned dstlen)
{
  const char* p = src;
  const char* e = src+srclen;
  unsigned count = 0;
  if (dstlen) for (;;) {
    unsigned char c;
    if (p >= e) {dst[count] = 0; return count;}
    c = *(unsigned char*)p;
    if (c < 0xC2) {
      dst[count] = c;
      p++;
    } else {
      int len; unsigned ucs = utf8decode(p,e,&len);
      p += len;
      if (ucs < 0x100) dst[count] = (char)ucs;
      else
      {
          if (!bHaveWarned4)
          {
              bHaveWarned4 = TRUE;
              CPLError(CE_Warning, CPLE_AppDefined,
                       "One or several characters couldn't be converted correctly from UTF-8 to ISO-8859-1.\n"
                       "This warning will not be emitted anymore.");
          }
          dst[count] = '?';
      }
    }
    if (++count >= dstlen) {dst[count-1] = 0; break;}
  }

  while (p < e) {
    if (!(*p & 0x80)) p++;
    else {
      int len;
      utf8decode(p,e,&len);
      p += len;
    }
    ++count;
  }
  return count;
}
