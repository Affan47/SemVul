luaD_adjusttop (StkId newtop) {
  int diff = newtop-(L->stack.top-L->stack.stack);
  if (diff <= 0)
    L->stack.top += diff;
  else {
    luaD_checkstack(diff);
    while (diff--)
      ttype(L->stack.top++) = LUA_T_NIL;
  }
}
