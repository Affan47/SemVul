tolua_ismodulemetatable (lua_State* L)
{
	int r = 0;
	if (lua_getmetatable(L,-1))
	{
		lua_pushstring(L,"__index");
		lua_rawget(L,-2);
		r = (lua_tocfunction(L,-1) == module_index_event);
		lua_pop(L,2);
	}
	return r;
}
