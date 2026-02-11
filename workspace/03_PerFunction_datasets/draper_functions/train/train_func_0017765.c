travtagmethods (lua_State *L, const TObject *o) {
  if (ttype(o) == LUA_TFUNCTION) {
    int e;
    for (e=0; e<TM_N; e++) {
      int t;
      for (t=0; t<=L->last_tag; t++)
        if (clvalue(o) == luaT_gettm(L, t, e))
          return luaT_eventname[e];
    }
  }
  return NULL;
}
