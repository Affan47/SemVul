unbase64_raw(const char* p, const char* lim, char* r, const unsigned char* index_64)
{
  int i;
  unsigned char c[4];
  unsigned char uc;

  while (p < lim) {
    i = 0;
    do {
      if (*p == '%' && p+2 < lim && IS_HEX(p[1]) && IS_HEX(p[2])) {

	uc = index_64[(HEX(p[1]) << 4) | HEX(p[2])];
	p += 3;
      } else
	uc = index_64[(int)*p++];
      if (uc != INVALID)
	c[i++] = uc;

      if (p == lim) {
	if (i < 4) {

	  if (i < 2) return r;
	  if (i == 2) c[2] = Eq;
	  c[3] = Eq;
	}
	break;
      }
    } while (i < 4);

    if (c[0] == Eq || c[1] == Eq) {
      ERR("Premature end of base64 data. (incomplete base64 input) c0(%x)", c[0]);
      break;
    }


    *r++ = (c[0] << 2) | ((c[1] & 0x30) >> 4);
    if (c[2] == Eq) break;
    *r++ = ((c[1] & 0x0f) << 4) | ((c[2] & 0x3c) >> 2);
    if (c[3] == Eq) break;
    *r++ = ((c[2] & 0x03) << 6) | c[3];
  }
  return r;
}
