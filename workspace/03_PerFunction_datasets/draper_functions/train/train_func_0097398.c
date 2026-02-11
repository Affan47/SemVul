luaV_lessthan (lua_State *L, const TValue *l, const TValue *r) {
  int res;
  lua_Number nl, nr;
  if (ttisinteger(l) && ttisinteger(r))
    return (ivalue(l) < ivalue(r));
  else if (tofloat(l, &nl) && tofloat(r, &nr))
    return luai_numlt(nl, nr);
  else if (ttisstring(l) && ttisstring(r))
    return l_strcmp(tsvalue(l), tsvalue(r)) < 0;
  else if ((res = luaT_callorderTM(L, l, r, TM_LT)) < 0)
    luaG_ordererror(L, l, r);
  return res;
}
