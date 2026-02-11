luaL_ref (lua_State *L, int t) {
  int ref;
  t = abs_index(L, t);
  if (lua_isnil(L, -1)) {
    lua_pop(L, 1);
    return LUA_REFNIL;
  }
  lua_rawgeti(L, t, FREELIST_REF);
  ref = (int)lua_tonumber(L, -1);
  lua_pop(L, 1);
  if (ref != 0) {
    lua_rawgeti(L, t, ref);
    lua_rawseti(L, t, FREELIST_REF);
  }
  else {
    ref = luaL_getn(L, t);
    if (ref < RESERVED_REFS)
      ref = RESERVED_REFS;
    ref++;
    luaL_setn(L, t, ref);
  }
  lua_rawseti(L, t, ref);
  return ref;
}
