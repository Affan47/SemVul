luaB_tonumber (lua_State *L) {
  int base = luaL_opt_int(L, 2, 10);
  if (base == 10) {
    luaL_checkany(L, 1);
    if (lua_isnumber(L, 1)) {
      lua_pushnumber(L, lua_tonumber(L, 1));
      return 1;
    }
  }
  else {
    const char *s1 = luaL_check_string(L, 1);
    char *s2;
    unsigned long n;
    luaL_arg_check(L, 2 <= base && base <= 36, 2, "base out of range");
    n = strtoul(s1, &s2, base);
    if (s1 != s2) {
      while (isspace((unsigned char)*s2)) s2++;
      if (*s2 == '\0') {
        lua_pushnumber(L, n);
        return 1;
      }
    }
  }
  lua_pushnil(L);
  return 1;
}
