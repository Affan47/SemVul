findlocal (lua_State *L, CallInfo *ci, int n) {
  const char *name;
  Proto *fp = getluaproto(ci);
  if (fp && (name = luaF_getlocalname(fp, n, currentpc(L, ci))) != NULL)
    return name;
  else {
    StkId limit = (ci == L->ci) ? L->top : (ci+1)->func;
    if (limit - ci->base >= n && n > 0)
      return "(*temporary)";
    else
      return NULL;
  }
}
