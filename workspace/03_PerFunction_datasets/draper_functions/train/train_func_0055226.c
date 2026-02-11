matchbalance (lua_State *L, const char *s, const char *p,
                                 struct Capture *cap) {
  if (*p == 0 || *(p+1) == 0)
    lua_error(L, "unbalanced pattern");
  if (*s != *p) return NULL;
  else {
    int b = *p;
    int e = *(p+1);
    int cont = 1;
    while (++s < cap->src_end) {
      if (*s == e) {
        if (--cont == 0) return s+1;
      }
      else if (*s == b) cont++;
    }
  }
  return NULL;
}
