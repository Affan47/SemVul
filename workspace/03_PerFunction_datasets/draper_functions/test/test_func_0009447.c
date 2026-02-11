tostring (lua_Object obj)
{
  TObject *o = luaI_Address(obj);
  switch (ttype(o)) {
    case LUA_T_NUMBER:  case LUA_T_STRING:
      return lua_getstring(obj);
    case LUA_T_ARRAY: case LUA_T_FUNCTION:
    case LUA_T_CFUNCTION: case LUA_T_NIL:
      return luaI_typenames[-ttype(o)];
    case LUA_T_USERDATA: {
      char *buff = luaI_buffer(30);
      sprintf(buff, "userdata: %p", o->value.ts->u.v);
      return buff;
    }
    default: return "<unknown object>";
  }
}
