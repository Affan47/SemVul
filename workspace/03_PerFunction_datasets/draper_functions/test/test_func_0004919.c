getstack (void) {
  lua_Object func = lua_stackedfunction(luaL_check_int(1));
  if (func == LUA_NOOBJECT)
    return;
  else {
    lua_Object result = getfuncinfo(func);
    int currline = lua_currentline(func);
    if (currline > 0)
      settabsi(result, "current", currline);
    lua_pushobject(result);
    lua_pushstring("func");
    lua_pushobject(func);
    lua_settable();
    lua_pushobject(result);
  }
}
