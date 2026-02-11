properties_newindex (lua_State *L)
{
  lua_pushvalue(L, 2);
  lua_rawget(L, lua_upvalueindex(1));
  if (!lua_isnil(L, -1))
  {
    lua_pushvalue(L, 1);
    lua_pushvalue(L, 3);

    lua_call(L, 2, 0);
    return 0;
  }
  return 0;
}
