str_char (void) {
  int i = 0;
  luaL_resetbuffer();
  while (lua_getparam(++i) != LUA_NOOBJECT) {
    double c = luaL_check_number(i);
    luaL_arg_check((unsigned char)c == c, i, "invalid value");
    luaL_addchar((int)c);
  }
  closeandpush();
}
