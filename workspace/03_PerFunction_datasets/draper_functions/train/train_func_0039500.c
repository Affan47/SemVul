luaB_settagmethod (lua_State *L) {
  int tag = luaL_check_int(L, 1);
  const char *event = luaL_check_string(L, 2);
  luaL_arg_check(L, lua_isfunction(L, 3) || lua_isnil(L, 3), 3,
                 "function or nil expected");
  if (strcmp(event, "gc") == 0)
    lua_error(L, "deprecated use: cannot set the `gc' tag method from Lua");
  lua_gettagmethod(L, tag, event);
  lua_pushvalue(L, 3);
  lua_settagmethod(L, tag, event);
  return 1;
}
