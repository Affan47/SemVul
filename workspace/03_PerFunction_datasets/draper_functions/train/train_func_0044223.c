is_in (int tok, int *toks) {
  int *t = toks;
  while (*t) {
    if (*t == tok)
      return t-toks;
    t++;
  }
  return -1;
}
