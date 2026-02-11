hashindex (Hash *t, Object *ref)
{
  long int h;
  switch (tag(ref)) {
    case LUA_T_NIL:
      lua_error ("unexpected type to index table");
      h = 0;
    case LUA_T_NUMBER:
      h = (long int)nvalue(ref); break;
    case LUA_T_STRING:
      h = tsvalue(ref)->hash; break;
    case LUA_T_FUNCTION:
      h = (IntPoint)ref->value.tf; break;
    case LUA_T_CFUNCTION:
      h = (IntPoint)fvalue(ref); break;
    case LUA_T_ARRAY:
      h = (IntPoint)avalue(ref); break;
    default:
      h = (IntPoint)uvalue(ref); break;
  }
  if (h < 0) h = -h;
  return h%nhash(t);
}
