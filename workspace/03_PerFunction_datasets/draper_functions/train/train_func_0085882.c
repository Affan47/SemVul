lua_dump (lua_State *L, lua_Chunkwriter writer, void *data) {
  int status;
  TObject *o;
  lua_lock(L);
  api_checknelems(L, 1);
  o = L->top - 1;
  if (isLfunction(o) && clvalue(o)->l.nupvalues == 0) {
    luaU_dump(L, clvalue(o)->l.p, writer, data);
    status = 1;
  }
  else
    status = 0;
  lua_unlock(L);
  return status;
}
