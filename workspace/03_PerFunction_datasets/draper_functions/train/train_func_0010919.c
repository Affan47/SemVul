luaI_print (void)
{
  int i = 1;
  lua_Object obj;
  while ((obj = lua_getparam(i++)) != LUA_NOOBJECT)
    printf("%s\n", tostring(obj));
}
