str_byte (lua_State *L) {
  size_t l;
  const char *s = luaL_check_lstr(L, 1, &l);
  long pos = posrelat(luaL_opt_long(L, 2, 1), l);
  luaL_arg_check(L, 0<pos && (size_t)pos<=l, 2,  "out of range");
  lua_pushnumber(L, (unsigned char)s[pos-1]);
  return 1;
}
