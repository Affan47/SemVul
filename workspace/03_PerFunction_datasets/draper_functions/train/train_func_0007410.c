lj_lib_checknum(lua_State *L, int narg)
{
  TValue *o = L->base + narg-1;
  if (!(o < L->top &&
	(tvisnumber(o) || (tvisstr(o) && lj_strscan_num(strV(o), o)))))
    lj_err_argt(L, narg, LUA_TNUMBER);
  if (LJ_UNLIKELY(tvisint(o))) {
    lua_Number n = (lua_Number)intV(o);
    setnumV(o, n);
    return n;
  } else {
    return numV(o);
  }
}
