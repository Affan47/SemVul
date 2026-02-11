luaL_optinteger(lua_State *L, int idx, lua_Integer def)
{
  cTValue *o = index2adr(L, idx);
  TValue tmp;
  lua_Number n;
  if (LJ_LIKELY(tvisint(o))) {
    return intV(o);
  } else if (LJ_LIKELY(tvisnum(o))) {
    n = numV(o);
  } else if (tvisnil(o)) {
    return def;
  } else {
    if (!(tvisstr(o) && lj_strscan_number(strV(o), &tmp)))
      lj_err_argt(L, idx, LUA_TNUMBER);
    if (tvisint(&tmp))
      return (lua_Integer)intV(&tmp);
    n = numV(&tmp);
  }
#if LJ_64
  return (lua_Integer)n;
#else
  return lj_num2int(n);
#endif
}
