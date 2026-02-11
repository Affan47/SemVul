tolua_bnd_takeownership (lua_State* L)
{
	int success = 0;
	if (lua_isuserdata(L,1))
	{
		if (lua_getmetatable(L,1))
		{
			lua_pop(L,1);

			#ifdef LUA_VERSION_NUM
			lua_gc(L, LUA_GCCOLLECT, 0);
			#else
			lua_setgcthreshold(L,0);
			#endif

			success = tolua_register_gc(L,1);
		}
	}
	lua_pushboolean(L,success!=0);
	return 1;
}
