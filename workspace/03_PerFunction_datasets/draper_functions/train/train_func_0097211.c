readdecesc (LexState *ls) {
  int c[3], i;
  int r = 0;
  for (i = 0; i < 3 && lisdigit(ls->current); i++) {
    c[i] = ls->current;
    r = 10*r + c[i] - '0';
    next(ls);
  }
  if (r > UCHAR_MAX)
    escerror(ls, c, i, "decimal escape too large");
  return r;
}
