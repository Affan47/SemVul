updatecache (CapState *cs, int v) {
  int idx = cs->ptop + 1;
  if (v != cs->valuecached) {
    getfromktable(cs, v);
    lua_replace(cs->L, idx);
    cs->valuecached = v;
  }
  return idx;
}
