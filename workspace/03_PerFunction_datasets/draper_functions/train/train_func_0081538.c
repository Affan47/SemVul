torch_DiskFile_seekEnd(lua_State *L)
{
  DiskFile *file = luaT_checkudata(L, 1, torch_DiskFile_id);

  luaL_argcheck(L, file->handle, 1, "attempt to use a closed file");

  if(fseek(file->handle, 0L, SEEK_END) < 0)
  {
    file->flags.hasError = 1;
    if(!file->flags.isQuiet)
      luaL_error(L, "unable to seek at end of file");
  }
  lua_settop(L, 1);
  return 1;
}
