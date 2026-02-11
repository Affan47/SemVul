lj_tab_new1(lua_State *L, uint32_t ahsize)
{
  GCtab *t = newtab(L, ahsize & 0xffffff, ahsize >> 24);
  clearapart(t);
  if (t->hmask > 0) clearhpart(t);
  return t;
}
