luaS_createudata (lua_State *L, void *udata, int tag) {
  int h1 = IntPoint(udata) & (L->udt.size-1);
  TString *ts;
  for (ts = L->udt.hash[h1]; ts; ts = ts->nexthash) {
    if (udata == ts->u.d.value && (tag == ts->u.d.tag || tag == LUA_ANYTAG))
      return ts;
  }

  ts = luaS_newudata(L, 0, udata);
  if (tag != LUA_ANYTAG)
    ts->u.d.tag = tag;
  return ts;
}
