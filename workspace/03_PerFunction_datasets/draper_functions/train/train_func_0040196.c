lua_tolstring(lua_State *L, int idx, size_t *len)
{
  TValue *o = index2adr(L, idx);
  GCstr *s;
  if (LJ_LIKELY(tvisstr(o))) {
    s = strV(o);
  } else if (tvisnumber(o)) {
    lj_gc_check(L);
    o = index2adr(L, idx);
    s = lj_str_fromnumber(L, o);
    setstrV(L, o, s);
  } else {
    if (len != NULL) *len = 0;
    return NULL;
  }
  if (len != NULL) *len = s->len;
  return strdata(s);
}
