callC (lua_CFunction f, StkId base) {
  struct C_Lua_Stack *cls = &L->Cstack;
  struct C_Lua_Stack oldCLS = *cls;
  StkId firstResult;
  int numarg = (L->stack.top-L->stack.stack) - base;
  cls->num = numarg;
  cls->lua2C = base;
  cls->base = base+numarg;
  if (L->callhook)
    luaD_callHook(base, NULL, 0);
  (*f)();
  if (L->callhook)
    luaD_callHook(base, NULL, 1);
  firstResult = cls->base;
  *cls = oldCLS;
  return firstResult;
}
