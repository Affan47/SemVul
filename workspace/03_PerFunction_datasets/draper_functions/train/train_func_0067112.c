dirp(lua_State *L)
{
  const char *s = luaL_checkstring(L, 1);
#ifdef LUA_WIN
  struct _stat buf;
  const char *last;
  if ((s[0]=='/' || s[0]=='\\') &&
      (s[1]=='/' || s[1]=='\\') && !s[2])
    return 1;
  last = s + strlen(s);
  if (*last=='/' || *last=='\\' || *last==':')
    {
      lua_settop(L, 1);
      lua_pushliteral(L, ".");
      lua_concat(L, 2);
      s = lua_tostring(L, -1);
    }
  if (_stat(s,&buf)==0)
    if (buf.st_mode & S_IFDIR)
      return 1;
#else
  struct stat buf;
  if (stat(s,&buf)==0)
    if (buf.st_mode & S_IFDIR)
      return 1;
#endif
  return 0;
}
