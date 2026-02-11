luaD_call (StkId base, int nResults)
{
  StkId firstResult;
  TObject *func = L->stack.stack+base-1;
  int i;
  switch (ttype(func)) {
    case LUA_T_CPROTO:
      ttype(func) = LUA_T_CMARK;
      firstResult = callC(fvalue(func), base);
      break;
    case LUA_T_PROTO:
      ttype(func) = LUA_T_PMARK;
      firstResult = luaV_execute(NULL, tfvalue(func), base);
      break;
    case LUA_T_CLOSURE: {
      Closure *c = clvalue(func);
      TObject *proto = &(c->consts[0]);
      ttype(func) = LUA_T_CLMARK;
      firstResult = (ttype(proto) == LUA_T_CPROTO) ?
                       callCclosure(c, fvalue(proto), base) :
                       luaV_execute(c, tfvalue(proto), base);
      break;
    }
    default: {

      TObject *im = luaT_getimbyObj(func, IM_FUNCTION);
      if (ttype(im) == LUA_T_NIL)
        lua_error("call expression not a function");
      luaD_callTM(im, (L->stack.top-L->stack.stack)-(base-1), nResults);
      return;
    }
  }

  if (nResults != MULT_RET)
    luaD_adjusttop(firstResult+nResults);

  base--;
  nResults = L->stack.top - (L->stack.stack+firstResult);
  for (i=0; i<nResults; i++)
    *(L->stack.stack+base+i) = *(L->stack.stack+firstResult+i);
  L->stack.top -= firstResult-base;
}
