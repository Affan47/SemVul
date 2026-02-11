str_find (lua_State *L) {
  size_t l1, l2;
  const char *s = luaL_check_lstr(L, 1, &l1);
  const char *p = luaL_check_lstr(L, 2, &l2);
  long init = posrelat(luaL_opt_long(L, 3, 1), l1) - 1;
  struct Capture cap;
  luaL_arg_check(L, 0 <= init && (size_t)init <= l1, 3, "out of range");
  if (lua_gettop(L) > 3 ||
      strpbrk(p, SPECIALS) == NULL) {
    const char *s2 = lmemfind(s+init, l1-init, p, l2);
    if (s2) {
      lua_pushnumber(L, s2-s+1);
      lua_pushnumber(L, s2-s+l2);
      return 2;
    }
  }
  else {
    int anchor = (*p == '^') ? (p++, 1) : 0;
    const char *s1=s+init;
    cap.src_end = s+l1;
    do {
      const char *res;
      cap.level = 0;
      if ((res=match(L, s1, p, &cap)) != NULL) {
        lua_pushnumber(L, s1-s+1);
        lua_pushnumber(L, res-s);
        return push_captures(L, &cap) + 2;
      }
    } while (s1++<cap.src_end && !anchor);
  }
  lua_pushnil(L);
  return 1;
}
