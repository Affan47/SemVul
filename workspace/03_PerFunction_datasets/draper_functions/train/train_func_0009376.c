findfile (lua_State *L, const char *name,
                                           const char *pname) {
  const char *path;
  int i = 0;
  while (name[i]) {
    if (!isalnum(name[i]) && name[i] != '_' && name[i] != '.') {
      luaL_error(L, "invalid module name '%s'", name);
      return NULL;
    }
    ++i;
  }
  lua_getfield(L, LUA_REGISTRYINDEX, LSB_CONFIG);
  if (lua_type(L, -1) != LUA_TTABLE) {
    return NULL;
  }
  name = luaL_gsub(L, name, ".", LUA_DIRSEP);
  lua_getfield(L, -2, pname);
  path = lua_tostring(L, -1);
  if (path == NULL)
    luaL_error(L, LUA_QL("package.%s") " must be a string", pname);
  lua_pushliteral(L, "");
  while ((path = pushnexttemplate(L, path)) != NULL) {
    const char *filename;
    filename = luaL_gsub(L, lua_tostring(L, -1), LUA_PATH_MARK, name);
    lua_remove(L, -2);
    if (readable(filename))
      return filename;
    lua_pushfstring(L, "\n\tno file " LUA_QS, filename);
    lua_remove(L, -2);
    lua_concat(L, 2);
  }
  return NULL;
}
