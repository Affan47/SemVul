findloader (lua_State *L, const char *name) {
  int i;
  luaL_Buffer msg;
  luaL_buffinit(L, &msg);
  lua_getfield(L, lua_upvalueindex(1), "searchers");
  if (!lua_istable(L, 3))
    luaL_error(L, LUA_QL("package.searchers") " must be a table");

  for (i = 1; ; i++) {
    lua_rawgeti(L, 3, i);
    if (lua_isnil(L, -1)) {
      lua_pop(L, 1);
      luaL_pushresult(&msg);
      luaL_error(L, "module " LUA_QS " not found:%s",
                    name, lua_tostring(L, -1));
    }
    lua_pushstring(L, name);
    lua_call(L, 1, 2);
    if (lua_isfunction(L, -2))
      return;
    else if (lua_isstring(L, -2)) {
      lua_pop(L, 1);
      luaL_addvalue(&msg);
    }
    else
      lua_pop(L, 2);
  }
}
