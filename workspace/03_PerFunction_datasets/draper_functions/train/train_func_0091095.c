lua_nextvar (void)
{
 Word next;
 lua_Object o = lua_getparam(1);
 if (o == LUA_NOOBJECT)
   lua_error("too few arguments to function `nextvar'");
 if (lua_getparam(2) != LUA_NOOBJECT)
   lua_error("too many arguments to function `nextvar'");
 if (lua_isnil(o))
   next = 0;
 else if (!lua_isstring(o))
 {
   lua_error("incorrect argument to function `nextvar'");
   return;
 }
 else
   next = luaI_findsymbolbyname(lua_getstring(o)) + 1;
 while (next < lua_ntable && s_tag(next) == LUA_T_NIL) next++;
 if (next < lua_ntable)
 {
  lua_pushstring(lua_table[next].varname->str);
  luaI_pushobject(&s_object(next));
 }
}
