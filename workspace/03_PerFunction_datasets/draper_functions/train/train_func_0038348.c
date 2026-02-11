lua_internaldostring (void)
{
  lua_Object err = lua_getparam(2);
  if (err != LUA_NOOBJECT) {
    luaL_arg_check(lua_isnil(err) || lua_isfunction(err), 2,
                   "must be a valid error handler");
    lua_pushobject(err);
    err = lua_seterrormethod();
  }
  if (lua_dostring(luaL_check_string(1)) == 0)
    if (passresults() == 0)
      lua_pushuserdata(NULL);
  if (err != LUA_NOOBJECT) {
    lua_pushobject(err);
    lua_seterrormethod();
  }
}
