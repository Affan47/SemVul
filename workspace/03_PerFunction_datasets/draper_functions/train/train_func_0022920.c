lua_setlocal (lua_State *L, const lua_Debug *ar, int n) {
  const char *name;
  StkId f = ar->_func;
  Proto *fp = getluaproto(f);
  L->top--;
  if (!fp) return NULL;
  name = luaF_getlocalname(fp, n, currentpc(f));
  if (!name || name[0] == '(') return NULL;
  *((f+1)+(n-1)) = *L->top;
  return name;
}
