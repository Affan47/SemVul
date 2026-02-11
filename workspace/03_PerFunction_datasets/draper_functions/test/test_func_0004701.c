auxresume (lua_State *L, lua_State *co, int narg) {
  int status;
  if (!lua_checkstack(co, narg))
    luaL_error(L, "too many arguments to resume");
  lua_xmove(L, co, narg);
  status = lua_resume(co, narg);
  if (status == 0) {
    int nres = lua_gettop(co);
    if (!lua_checkstack(L, nres))
      luaL_error(L, "too many results to resume");
    lua_xmove(co, L, nres);
    return nres;
  }
  else {
    lua_xmove(co, L, 1);
    return -1;
  }
}
