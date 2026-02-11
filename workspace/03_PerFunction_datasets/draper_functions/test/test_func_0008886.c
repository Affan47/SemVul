luaV_pack (StkId firstel, int nvararg, TObject *tab) {
  TObject *firstelem = L->stack.stack+firstel;
  int i;
  Hash *htab;
  if (nvararg < 0) nvararg = 0;
  htab = avalue(tab) = luaH_new(nvararg+1);
  ttype(tab) = LUA_T_ARRAY;
  for (i=0; i<nvararg; i++)
    luaH_setint(htab, i+1, firstelem+i);
  luaV_setn(htab, nvararg);
}
