torch_DiskFile_synchronize(lua_State *L)
{
  DiskFile *file = luaT_checkudata(L, 1, torch_DiskFile_id);
  if(!file->handle)
    luaL_error(L, "attempt to use a closed file");
  fflush(file->handle);
  lua_settop(L, 1);
  return 1;
}
