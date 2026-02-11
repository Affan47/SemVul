decode(Char *to, const char *s,
			   size_t slen, const char **rest)
{
  Char *start = to;
  while (slen > 0) {
    unsigned char c = *(unsigned char *)s;
    if (!(c & 0x80)) {
      *to++ = c;
      s++;
      slen--;
    }
    else if (129 <= c && c <= 159) {
      if (slen < 2)
	break;
      s++;
      slen -= 2;
      unsigned char c2 = *(unsigned char *)s++;
      unsigned short n = ((c - 112) << 9) | c2;
      if (64 <= c2 && c2 <= 127)
	n -= 31 + (1 << 8);
      else if (c2 <= 158)
	n -= 32 + (1 << 8);
      else if (c2 <= 252)
	n -= 126;
      else
	continue;
      n |= 0x8080;
      *to++ = n;
    }
    else if (224 <= c && c <= 239) {
      if (slen < 2)
	break;
      s++;
      slen -= 2;
      unsigned char c2 = *(unsigned char *)s++;
      unsigned short n = ((c - 176) << 9) | c2;
      if (64 <= c2 && c2 <= 127)
	n -= 31 + (1 << 8);
      else if (c2 <= 158)
	n -= 32 + (1 << 8);
      else if (c2 <= 252)
	n -= 126;
      else
	continue;
      n |= 0x8080;
      *to++ = n;
    }
    else if (161 <= c && c <= 223) {
      slen--;
      s++;
      *to++ = c;
    }
    else {

      slen--;
      s++;
    }
  }
  *rest = s;
  return to - start;
}
