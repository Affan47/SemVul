luaB_tinsert (lua_State *L) {
  int v = lua_gettop(L);
  int n, pos;
  luaL_checktype(L, 1, LUA_TTABLE);
  n = lua_getn(L, 1);
  if (v == 2)
    pos = n+1;
  else
    pos = luaL_check_int(L, 2);
  lua_pushstring(L, "n");
  lua_pushnumber(L, n+1);
  lua_rawset(L, 1);
  for (; n>=pos; n--) {
    lua_rawgeti(L, 1, n);
    lua_rawseti(L, 1, n+1);
  }
  lua_pushvalue(L, v);
  lua_rawseti(L, 1, pos);
  return 0;
}
