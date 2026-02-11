luaI_initsymbol (void)
{
  int i;
  lua_maxsymbol = BUFFER_BLOCK;
  lua_table = newvector(lua_maxsymbol, Symbol);
  for (i=0; i<INTFUNCSIZE; i++)
  {
    Word n = luaI_findsymbolbyname(int_funcs[i].name);
    s_tag(n) = LUA_T_CFUNCTION; s_fvalue(n) = int_funcs[i].func;
  }
}
