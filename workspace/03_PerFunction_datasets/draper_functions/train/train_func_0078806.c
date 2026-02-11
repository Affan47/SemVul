luaL_checknumber(lua_State *L, int idx)
{
  cTValue *o = index2adr(L, idx);
  TValue tmp;
  if (LJ_LIKELY(tvisnumber(o)))
    return numberVnum(o);
  else if (!(tvisstr(o) && lj_strscan_num(strV(o), &tmp)))
    lj_err_argt(L, idx, LUA_TNUMBER);
  return numV(&tmp);
}
