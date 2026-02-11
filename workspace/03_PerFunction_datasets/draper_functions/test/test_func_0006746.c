hashindex (TObject *ref)
{
  long int h;
  switch (ttype(ref)) {
    case LUA_T_NUMBER:
      h = (long int)nvalue(ref);
      break;
    case LUA_T_STRING: case LUA_T_USERDATA:
      h = (IntPoint)tsvalue(ref);
      break;
    case LUA_T_ARRAY:
      h = (IntPoint)avalue(ref);
      break;
    case LUA_T_PROTO:
      h = (IntPoint)tfvalue(ref);
      break;
    case LUA_T_CPROTO:
      h = (IntPoint)fvalue(ref);
      break;
    case LUA_T_CLOSURE:
      h = (IntPoint)clvalue(ref);
      break;
    default:
      lua_error("unexpected type to index table");
      h = 0;
  }
  return (h >= 0 ? h : -(h+1));
}
