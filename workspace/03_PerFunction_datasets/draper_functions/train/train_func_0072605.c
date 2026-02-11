travglobals (lua_State *L, const TObject *o) {
  Hash *g = L->gt;
  int i;
  for (i=0; i<g->size; i++) {
    if (luaO_equalObj(o, val(node(g, i))) &&
        ttype(key(node(g, i))) == LUA_TSTRING)
      return tsvalue(key(node(g, i)))->str;
  }
  return NULL;
}
