do_operator (lua_State* L, const char* op)
{
	if (lua_isuserdata(L,1))
	{

		lua_pushvalue(L,1);
		while (lua_getmetatable(L,-1))
		{
			lua_remove(L,-2);
			lua_pushstring(L,op);
			lua_rawget(L,-2);
			if (lua_isfunction(L,-1))
			{
				lua_pushvalue(L,1);
				lua_pushvalue(L,2);
				lua_call(L,2,1);
				return 1;
			}
			lua_settop(L,3);
		}
	}
	tolua_error(L,"Attempt to perform operation on an invalid operand",NULL);
	return 0;
}
