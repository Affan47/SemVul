aux_do (lua_State *L, int status) {
  if (status == 0) {
    status = lua_pcall(L, 0, LUA_MULTRET, 0);
  }
  callalert(L, status);
  return status;
}
