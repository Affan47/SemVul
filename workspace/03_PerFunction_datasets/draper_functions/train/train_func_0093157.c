luaV_settable (TObject *t, int mode)
{
  struct Stack *S = &L->stack;
  TObject *im = (mode == 0) ? NULL : luaT_getimbyObj(t, IM_SETTABLE);
  if (ttype(t) == LUA_T_ARRAY && (im == NULL || ttype(im) == LUA_T_NIL)) {
    TObject *h = luaH_set(avalue(t), t+1);
    *h = *(S->top-1);
    S->top -= (mode == 2) ? 1 : 3;
  }
  else {
    if (im && ttype(im) != LUA_T_NIL) {
      if (mode == 2) {
        *(S->top+1) = *(L->stack.top-1);
        *(S->top) = *(t+1);
        *(S->top-1) = *t;
        S->top += 2;
      }
      luaD_callTM(im, 3, 0);
    }
    else
      lua_error("indexed expression not a table");
  }
}
