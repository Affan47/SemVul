tolua_variable (lua_State* L, const char* name, lua_CFunction get, lua_CFunction set)
{

	lua_pushstring(L,".get");
	lua_rawget(L,-2);
	if (!lua_istable(L,-1))
	{

		lua_pop(L,1);
		lua_newtable(L);
	 lua_pushstring(L,".get");
		lua_pushvalue(L,-2);
		lua_rawset(L,-4);
	}
	lua_pushstring(L,name);
	lua_pushcfunction(L,get);
 lua_rawset(L,-3);
	lua_pop(L,1);


	if (set)
	{
		lua_pushstring(L,".set");
		lua_rawget(L,-2);
		if (!lua_istable(L,-1))
		{

			lua_pop(L,1);
			lua_newtable(L);
			lua_pushstring(L,".set");
			lua_pushvalue(L,-2);
			lua_rawset(L,-4);
		}
		lua_pushstring(L,name);
		lua_pushcfunction(L,set);
		lua_rawset(L,-3);
		lua_pop(L,1);
	}
}
