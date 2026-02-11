luaB_foreach (void) {
  Hash *a = gethash(1);
  int i;
  TObject f;
  f = *luaA_Address(luaL_functionarg(2));
  luaD_checkstack(3);
  for (i=0; i<a->nhash; i++) {
    Node *nd = &(a->node[i]);
    if (ttype(val(nd)) != LUA_T_NIL) {
      *(L->stack.top++) = f;
      *(L->stack.top++) = *ref(nd);
      *(L->stack.top++) = *val(nd);
      luaD_calln(2, 1);
      if (ttype(L->stack.top-1) != LUA_T_NIL)
        return;
      L->stack.top--;
    }
  }
}
