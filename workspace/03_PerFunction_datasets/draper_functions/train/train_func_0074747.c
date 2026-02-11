Pfiles(lua_State *L)
{
	const char *path = luaL_optstring(L, 1, ".");
	DIR *d = opendir(path);
	if (d == NULL)
		return pusherror(L, path);
	else
	{
		lua_pushlightuserdata(L, d);
		lua_pushcclosure(L, aux_files, 1);
		return 1;
	}
}
