incomplete (int status) {
  if (status == LUA_ERRSYNTAX &&
         strstr(lua_tostring(L, -1), "near `<eof>'") != NULL) {
    lua_pop(L, 1);
    return 1;
  }
  else
    return 0;
}
