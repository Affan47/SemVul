lua_next (lua_Object o, int i) {
  TObject *t = Address(o);
  if (ttype(t) != LUA_T_ARRAY)
    lua_error("API error - object is not a table in `lua_next'");
  i = luaA_next(avalue(t), i);
  top2LC((i==0) ? 0 : 2);
  return i;
}
