luaL_argerror (int numarg, char *extramsg) {
  lua_Function f = lua_stackedfunction(0);
  char *funcname;
  lua_getobjname(f, &funcname);
  numarg -= lua_nups(f);
  if (funcname == NULL)
    funcname = "?";
  if (extramsg == NULL)
    luaL_verror("bad argument #%d to function `%.50s'", numarg, funcname);
  else
    luaL_verror("bad argument #%d to function `%.50s' (%.100s)",
                    numarg, funcname, extramsg);
}
