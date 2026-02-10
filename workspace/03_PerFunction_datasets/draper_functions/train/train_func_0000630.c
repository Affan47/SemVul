lj_cf_package_require(lua_State *L)
{
  const char *name = luaL_checkstring(L, 1);
  int i;
  lua_settop(L, 1);
  lua_getfield(L, LUA_REGISTRYINDEX, "_LOADED");
  lua_getfield(L, 2, name);
  if (lua_toboolean(L, -1)) {
    if (lua_touserdata(L, -1) == sentinel)
      luaL_error(L, "loop or previous error loading module " LUA_QS, name);
    return 1;
  }

  lua_getfield(L, LUA_ENVIRONINDEX, "loaders");
  if (!lua_istable(L, -1))
    luaL_error(L, LUA_QL("package.loaders") " must be a table");
  lua_pushliteral(L, "");
  for (i = 1; ; i++) {
    lua_rawgeti(L, -2, i);
    if (lua_isnil(L, -1))
      luaL_error(L, "module " LUA_QS " not found:%s",
		 name, lua_tostring(L, -2));
    lua_pushstring(L, name);
    lua_call(L, 1, 1);
    if (lua_isfunction(L, -1))
      break;
    else if (lua_isstring(L, -1))
      lua_concat(L, 2);
    else
      lua_pop(L, 1);
  }
  lua_pushlightuserdata(L, sentinel);
  lua_setfield(L, 2, name);
  lua_pushstring(L, name);
  lua_call(L, 1, 1);
  if (!lua_isnil(L, -1))
    lua_setfield(L, 2, name);
  lua_getfield(L, 2, name);
  if (lua_touserdata(L, -1) == sentinel) {
    lua_pushboolean(L, 1);
    lua_pushvalue(L, -1);
    lua_setfield(L, 2, name);
  }
  lj_lib_checkfpu(L);
  return 1;
}
