tolua_register_gc (lua_State* L, int lo)
{
 int success = 1;
 void *value = *(void **)lua_touserdata(L,lo);
 lua_pushstring(L,"tolua_gc");
 lua_rawget(L,LUA_REGISTRYINDEX);
	lua_pushlightuserdata(L,value);
	lua_rawget(L,-2);
	if (!lua_isnil(L,-1))
		success = 0;
	else
	{
		lua_pushlightuserdata(L,value);
		lua_getmetatable(L,lo);
		lua_rawset(L,-4);
	}
	lua_pop(L,2);
	return success;
}
