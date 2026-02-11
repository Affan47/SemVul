tolua_isusertype (lua_State* L, int lo, const char* type, int def, tolua_Error* err)
{
	if (def && lua_gettop(L)<abs(lo))
		return 1;
	if (lua_isnil(L,lo) || lua_isusertype(L,lo,type))
		return 1;
	err->index = lo;
	err->array = 0;
	err->type = type;
	return 0;
}
