readdecesc (LexState *ls) {
  int i;
  int r = 0;
  for (i = 0; i < 3 && lisdigit(ls->current); i++) {
    r = 10*r + ls->current - '0';
    save_and_next(ls);
  }
  esccheck(ls, r <= UCHAR_MAX, "decimal escape too large");
  luaZ_buffremove(ls->buff, i);
  return r;
}
