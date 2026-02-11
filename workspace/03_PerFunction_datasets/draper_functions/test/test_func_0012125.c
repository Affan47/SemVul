lua_getlocal (lua_Function func, int local_number, char **name)
{
  TObject *f = luaI_Address(func);
  *name = luaI_getlocalname(f->value.tf, local_number, lua_currentline(func));
  if (*name)
  {


    return Ref((f+2)+(local_number-1));
  }
  else
    return LUA_NOOBJECT;
}
