lj_lib_checkfunc(lua_State *L, int narg)
{
  TValue *o = L->base + narg-1;
  if (!(o < L->top && tvisfunc(o)))
    lj_err_argt(L, narg, LUA_TFUNCTION);
  return funcV(o);
}
