make_simple_sexp_from_hexstr (const char *line, size_t *nscanned)
{
  size_t n, len;
  const char *s;
  unsigned char *buf;
  unsigned char *p;
  char numbuf[50], *numbufp;
  size_t numbuflen;

  for (n=0, s=line; hexdigitp (s); s++, n++)
    ;
  if (nscanned)
    *nscanned = n;
  if (!n)
    return NULL;
  len = ((n+1) & ~0x01)/2;
  numbufp = smklen (numbuf, sizeof numbuf, len, &numbuflen);
  buf = xtrymalloc (1 + numbuflen + len + 1 + 1);
  if (!buf)
    return NULL;
  buf[0] = '(';
  p = (unsigned char *)stpcpy ((char *)buf+1, numbufp);
  s = line;
  if ((n&1))
    {
      *p++ = xtoi_1 (s);
      s++;
      n--;
    }
  for (; n > 1; n -=2, s += 2)
    *p++ = xtoi_2 (s);
  *p++ = ')';
  *p = 0;

  return buf;
}
