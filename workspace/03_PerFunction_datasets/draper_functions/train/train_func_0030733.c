sort_comp (lua_Object f, TObject *a, TObject *b) {

  if (f != LUA_NOOBJECT) {
    *(L->stack.top) = *luaA_Address(f);
    *(L->stack.top+1) = *a;
    *(L->stack.top+2) = *b;
    L->stack.top += 3;
    luaD_calln(2, 1);
  }
  else {
    *(L->stack.top) = *a;
    *(L->stack.top+1) = *b;
    L->stack.top += 2;
    luaV_comparison(LUA_T_NUMBER, LUA_T_NIL, LUA_T_NIL, IM_LT);
  }
  return ttype(--(L->stack.top)) != LUA_T_NIL;
}
