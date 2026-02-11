str_find (lua_State *L) {
  size_t l1, l2;
  const char *s = luaL_checklstring(L, 1, &l1);
  const char *p = luaL_checklstring(L, 2, &l2);
  sint32 init = posrelat(luaL_optlong(L, 3, 1), l1) - 1;
  if (init < 0) init = 0;
  else if ((size_t)(init) > l1) init = (sint32)l1;
  if (lua_toboolean(L, 4) ||
      strpbrk(p, SPECIALS) == NULL) {

    const char *s2 = lmemfind(s+init, l1-init, p, l2);
    if (s2) {
      lua_pushnumber(L, (lua_Number)(s2-s+1));
      lua_pushnumber(L, (lua_Number)(s2-s+l2));
      return 2;
    }
  }
  else {
    MatchState ms;
    int anchor = (*p == '^') ? (p++, 1) : 0;
    const char *s1=s+init;
    ms.L = L;
    ms.src_init = s;
    ms.src_end = s+l1;
    do {
      const char *res;
      ms.level = 0;
      if ((res=match(&ms, s1, p)) != NULL) {
        lua_pushnumber(L, (lua_Number)(s1-s+1));
        lua_pushnumber(L, (lua_Number)(res-s));
        return push_captures(&ms, NULL, 0) + 2;
      }
    } while (s1++<ms.src_end && !anchor);
  }
  lua_pushnil(L);
  return 1;
}
