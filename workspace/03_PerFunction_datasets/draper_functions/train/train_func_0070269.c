torch_DiskFile_readString(lua_State *L)
{
  DiskFile *file = luaT_checkudata(L, 1, torch_DiskFile_id);
  const char *format = luaL_checkstring(L, 2);
  luaL_argcheck(L, (strlen(format) >= 2 ? (format[0] == '*') && (format[1] == 'a' || format[1] == 'l') : 0), 2, "format must be '*a' or '*l'");


#define TBRS_BSZ 1024L

  if(format[1] == 'a')
  {
    char *p = luaT_alloc(L, TBRS_BSZ);
    long total = TBRS_BSZ;
    long pos = 0L;

    for (;;)
    {
      if(total-pos == 0)
      {
        total += TBRS_BSZ;
        p = luaT_realloc(L, p, total);
      }
      pos += fread(p+pos, 1, total-pos, file->handle);
      if (pos < total)
      {
        if(pos == 0L)
        {
          luaT_free(L, p);
          file->flags.hasError = 1;
          if(!file->flags.isQuiet)
            luaL_error(L, "read error: read 0 blocks instead of 1");
          return 0;
        }
        lua_pushlstring(L, p, pos);
        luaT_free(L, p);
        return 1;
      }
    }
  }
  else
  {
    char *p = luaT_alloc(L, TBRS_BSZ);
    long total = TBRS_BSZ;
    long pos = 0L;
    long size;

    for (;;)
    {
      if(total-pos <= 1)
      {
        total += TBRS_BSZ;
        p = luaT_realloc(L, p, total);
      }
      if (fgets(p+pos, total-pos, file->handle) == NULL)
      {
        if(pos == 0L)
        {
          luaT_free(L, p);
          file->flags.hasError = 1;
          if(!file->flags.isQuiet)
            luaL_error(L, "read error: read 0 blocks instead of 1");
          return 0;
        }
        lua_pushlstring(L, p, pos);
        luaT_free(L, p);
        return 1;
      }
      size = strlen(p+pos);
      if (size == 0L || (p+pos)[size-1] != '\n')
      {
        pos += size;
      }
      else
      {
        pos += size-1L;
        lua_pushlstring(L, p, pos);
        luaT_free(L, p);
        return 1;
      }
    }
  }
  return 0;
}
