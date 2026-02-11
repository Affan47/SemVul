lua_gettagmethod (lua_State *L, int t, const char *event) {
  int e;
  e = luaI_checkevent(L, event, t);
  checktag(L, t);
  if (luaT_validevent(t, e) && luaT_gettm(L, t, e)) {
    clvalue(L->top) = luaT_gettm(L, t, e);
    ttype(L->top) = LUA_TFUNCTION;
  }
  else
    ttype(L->top) = LUA_TNIL;
  incr_top;
}
