lua_arith (lua_State *L, int op) {
  lua_lock(L);
  if (op != LUA_OPUNM && op != LUA_OPBNOT)
    api_checknelems(L, 2);
  else {
    api_checknelems(L, 1);
    setobjs2s(L, L->top, L->top - 1);
    L->top++;
  }

  luaO_arith(L, op, L->top - 2, L->top - 1, L->top - 2);
  L->top--;
  lua_unlock(L);
}
