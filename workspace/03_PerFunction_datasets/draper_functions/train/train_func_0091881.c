io_close (lua_State *L) {
  if (lua_isnone(L, 1) && lua_type(L, lua_upvalueindex(1)) == LUA_TTABLE) {
    lua_pushstring(L, IO_OUTPUT);
    lua_rawget(L, lua_upvalueindex(1));
  }
  return pushresult(L, aux_close(L), NULL);
}
