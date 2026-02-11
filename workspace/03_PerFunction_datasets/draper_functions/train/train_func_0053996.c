lua_settop(lua_State *L, int idx)
{
  if (idx >= 0) {
    api_check(L, idx <= tvref(L->maxstack) - L->base);
    if (L->base + idx > L->top) {
      if (L->base + idx >= tvref(L->maxstack))
	lj_state_growstack(L, (MSize)idx - (MSize)(L->top - L->base));
      do { setnilV(L->top++); } while (L->top < L->base + idx);
    } else {
      L->top = L->base + idx;
    }
  } else {
    api_check(L, -(idx+1) <= (L->top - L->base));
    L->top += idx+1;
  }
}
