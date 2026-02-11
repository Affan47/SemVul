getnum(FILE *f, unsigned *np, const char *fn) {
  unsigned n;
  int c = getc(f);
  if (c < '0' || c > '9') badinput(fn);
  n = c - '0';
  while((c = getc(f)) >= '0' && c <= '9') {
    c -= '0';
    if (0xffffffff / 10 - c < n) badinput(fn);
    n = n * 10 + c;
  }
  *np = n;
  return c;
}
