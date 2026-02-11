lua_settable (lua_State *L, int index) {
  StkId t = Index(L, index);
  StkId top = L->top;
  luaV_settable(L, t, top-2);
  L->top = top-2;
}
