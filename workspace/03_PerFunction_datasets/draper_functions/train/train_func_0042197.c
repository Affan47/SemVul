luaV_objlen (lua_State *L, StkId ra, const TValue *rb) {
  const TValue *tm;
  switch (ttypenv(rb)) {
    case LUA_TTABLE: {
      Table *h = hvalue(rb);
      tm = fasttm(L, h->metatable, TM_LEN);
      if (tm) break;
      setnvalue(ra, cast_num(luaH_getn(h)));
      return;
    }
    case LUA_TSTRING: {
      setnvalue(ra, cast_num(tsvalue(rb)->len));
      return;
    }
    default: {
      tm = luaT_gettmbyobj(L, rb, TM_LEN);
      if (ttisnil(tm))
        luaG_typeerror(L, rb, "get length of");
      break;
    }
  }
  callTM(L, tm, rb, rb, ra, 1);
}
