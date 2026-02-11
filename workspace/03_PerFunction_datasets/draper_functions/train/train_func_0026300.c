luaV_gettable (lua_State *L, const TValue *t, TValue *key, StkId val) {
  int loop;
  for (loop = 0; loop < MAXTAGLOOP; loop++) {
    const TValue *tm;
    if (ttistable(t)) {
      Table *h = hvalue(t);
      const TValue *res = luaH_get(h, key);
      if (!ttisnil(res) ||
          (tm = fasttm(L, h->metatable, TM_INDEX)) == NULL) {
        setobj2s(L, val, res);
        return;
      }

    }
    else if (ttisnil(tm = luaT_gettmbyobj(L, t, TM_INDEX)))
      luaG_typeerror(L, t, "index");
    if (ttisfunction(tm)) {
      callTMres(L, val, tm, t, key);
      return;
    }
    t = tm;
  }
  luaG_runerror(L, "loop in gettable");
}
