seterrorobj (lua_State *L, int errcode, StkId oldtop) {
  switch (errcode) {
    case LUA_ERRMEM: {
      setsvalue2s(oldtop, luaS_new(L, MEMERRMSG));
      break;
    }
    case LUA_ERRERR: {
      setsvalue2s(oldtop, luaS_new(L, "error in error handling"));
      break;
    }
    case LUA_ERRSYNTAX:
    case LUA_ERRRUN: {
      setobjs2s(oldtop, L->top - 1);
      break;
    }
  }
  L->top = oldtop + 1;
}
