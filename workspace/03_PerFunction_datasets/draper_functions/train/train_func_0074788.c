tolua_isvalue (lua_State* L, int lo, int def, tolua_Error* err)
{
	if (def || abs(lo)<=lua_gettop(L))
		return 1;
	err->index = lo;
	err->array = 0;
	err->type = "value";
	return 0;
}
