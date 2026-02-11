storeatubox (lua_State* L, int lo)
{
	#ifdef LUA_VERSION_NUM
		lua_getfenv(L, lo);
		if (lua_rawequal(L, -1, TOLUA_NOPEER)) {
			lua_pop(L, 1);
			lua_newtable(L);
			lua_pushvalue(L, -1);
			lua_setfenv(L, lo);
		};
		lua_insert(L, -3);
		lua_settable(L, -3);
		lua_pop(L, 1);
	#else

		lua_pushstring(L,"tolua_peers");
		lua_rawget(L,LUA_REGISTRYINDEX);
		lua_pushvalue(L,lo);
		lua_rawget(L,-2);
		if (!lua_istable(L,-1))
		{
			lua_pop(L,1);
			lua_newtable(L);
			lua_pushvalue(L,1);
			lua_pushvalue(L,-2);
			lua_rawset(L,-4);
		}
		lua_insert(L,-4);
		lua_pop(L,1);
		lua_rawset(L,-3);
		lua_pop(L,1);
	#endif
}
