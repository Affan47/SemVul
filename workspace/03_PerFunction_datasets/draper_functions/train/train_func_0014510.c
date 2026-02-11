luaG_typeerror (lua_State *L, const TObject *o, const char *op) {
  const char *name = NULL;
  const char *t = luaT_typenames[ttype(o)];
  const char *kind = (isinstack(L->ci, o)) ?
                         getobjname(L->ci, o - L->base, &name) : NULL;
  if (kind)
    luaG_runerror(L, "attempt to %s %s `%s' (a %s value)",
                op, kind, name, t);
  else
    luaG_runerror(L, "attempt to %s a %s value", op, t);
}
