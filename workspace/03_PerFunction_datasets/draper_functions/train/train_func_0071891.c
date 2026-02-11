tolua_getfieldboolean (lua_State* L, int lo, int index, int def)
{
 int v;
 lua_pushnumber(L,index);
 lua_gettable(L,lo);
 v = lua_isnil(L,-1) ? 0 : lua_toboolean(L,-1);
 lua_pop(L,1);
 return v;
}
