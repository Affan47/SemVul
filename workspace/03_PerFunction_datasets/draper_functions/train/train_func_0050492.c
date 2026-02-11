luaT_pushmetaclass(lua_State *L, const void *id)
{
  luaT_pushmetatable(L, id);
  if(!lua_isnil(L, -1))
  {
    if(!lua_getmetatable(L, -1))
      luaL_error(L, "internal error: cannot find metaclass");
    lua_remove(L, -2);
  }
}
