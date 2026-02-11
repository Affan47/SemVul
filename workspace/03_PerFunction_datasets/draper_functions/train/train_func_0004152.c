adjust_varargs (lua_State *L, int nfixargs, StkId base) {
  int i;
  Table *htab;
  TObject nname;
  int actual = L->top - base;
  if (actual < nfixargs) {
    luaD_checkstack(L, nfixargs - actual);
    for (; actual < nfixargs; ++actual)
      setnilvalue(L->top++);
  }
  actual -= nfixargs;
  htab = luaH_new(L, actual, 1);
  for (i=0; i<actual; i++)
    setobj2n(luaH_setnum(L, htab, i+1), L->top - actual + i);

  setsvalue(&nname, luaS_newliteral(L, "n"));
  setnvalue(luaH_set(L, htab, &nname), cast(lua_Number, actual));
  L->top -= actual;
  sethvalue(L->top, htab);
  incr_top(L);
}
