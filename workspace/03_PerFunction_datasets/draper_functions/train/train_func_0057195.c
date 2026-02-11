nextword(const char **bufp_io, const char **word_r, int *l_r) {
  const char *p, *q;

  p= *bufp_io;
  while (ctype_whitespace(*p)) p++;
  if (!*p) return 0;

  q= p;
  while (*q && !ctype_whitespace(*q)) q++;

  *l_r= q-p;
  *word_r= p;
  *bufp_io= q;

  return 1;
}
