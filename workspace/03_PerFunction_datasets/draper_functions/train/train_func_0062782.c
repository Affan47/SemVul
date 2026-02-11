restore_stack_limit (lua_State *L) {
  if (L->top - L->stack < L->stacksize - 1)
    L->stack_last = L->stack + (L->stacksize-1);
}
