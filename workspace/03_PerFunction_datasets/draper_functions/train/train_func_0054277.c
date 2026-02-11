Pputenv(lua_State *L)
{
	size_t l;
	const char *s=luaL_checklstring(L, 1, &l);
	char *e=malloc(++l);
	return pushresult(L, (e==NULL) ? -1 : putenv(memcpy(e,s,l)), s);
}
