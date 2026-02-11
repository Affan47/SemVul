luaD_callHook (StkId base, TProtoFunc *tf, int isreturn)
{
  struct C_Lua_Stack oldCLS = L->Cstack;
  StkId old_top = L->Cstack.lua2C = L->Cstack.base = L->stack.top-L->stack.stack;
  L->Cstack.num = 0;
  if (isreturn)
    (*lua_callhook)(LUA_NOOBJECT, "(return)", 0);
  else {
    TObject *f = L->stack.stack+base-1;
    if (tf)
      (*lua_callhook)(Ref(f), tf->fileName->str, tf->lineDefined);
    else
      (*lua_callhook)(Ref(f), "(C)", -1);
  }
  L->stack.top = L->stack.stack+old_top;
  L->Cstack = oldCLS;
}
