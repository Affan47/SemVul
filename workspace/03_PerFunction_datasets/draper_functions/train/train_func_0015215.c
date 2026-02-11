f_opttype(lua_State *L, int index, const char *name, int type)
{
  lua_getfield(L,index,name);
  if (lua_isnoneornil(L, -1))
    return false;
  f_checktype(L, 0, name, type);
  return true;
}
