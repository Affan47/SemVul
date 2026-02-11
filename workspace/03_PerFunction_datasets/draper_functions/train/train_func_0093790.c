passresults (void)
{
  int arg = 0;
  lua_Object obj;
  while ((obj = lua_getresult(++arg)) != LUA_NOOBJECT)
    lua_pushobject(obj);
  return arg-1;
}
