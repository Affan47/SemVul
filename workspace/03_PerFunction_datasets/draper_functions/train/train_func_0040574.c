luaQ_private_noerr(lua_State *L)
{
  QtLuaEngine::Private *d = 0;
  lua_pushlightuserdata(L, (void*)engineKey);
  lua_rawget(L, LUA_REGISTRYINDEX);
  if (lua_islightuserdata(L, -1))
    d = static_cast<QtLuaEngine::Private*>(lua_touserdata(L, -1));
  lua_pop(L, 1);
  return d;
}
