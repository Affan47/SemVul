db_sethook (lua_State *L) {
  int arg, mask, count;
  lua_Hook func;
  lua_State *L1 = getthread(L, &arg);
  if (lua_isnoneornil(L, arg+1)) {
    lua_settop(L, arg+1);
    func = NULL; mask = 0; count = 0;
  }
  else {
    const char *smask = luaL_checkstring(L, arg+2);
    luaL_checktype(L, arg+1, LUA_TFUNCTION);
    count = (int)luaL_optinteger(L, arg + 3, 0);
    func = hookf; mask = makemask(smask, count);
  }
  if (lua_rawgetp(L, LUA_REGISTRYINDEX, &HOOKKEY) == LUA_TNIL) {
    lua_createtable(L, 0, 2);
    lua_pushvalue(L, -1);
    lua_rawsetp(L, LUA_REGISTRYINDEX, &HOOKKEY);
    lua_pushstring(L, "k");
    lua_setfield(L, -2, "__mode");
    lua_pushvalue(L, -1);
    lua_setmetatable(L, -2);
  }
  lua_pushthread(L1); lua_xmove(L1, L, 1);
  lua_pushvalue(L, arg + 1);
  lua_rawset(L, -3);
  lua_sethook(L1, func, mask, count);
  return 0;
}
