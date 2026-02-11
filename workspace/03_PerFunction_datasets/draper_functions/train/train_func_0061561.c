getfuncname (lua_State *L, StkId f, const char **name) {
  StkId func = aux_stackedfunction(L, 0, f);
  if (!isLmark(func))
    return NULL;
  else {
    Proto *p = infovalue(func)->func->f.l;
    int pc = currentpc(func);
    Instruction i;
    if (pc == -1) return NULL;
    i = p->code[pc];
    switch (GET_OPCODE(i)) {
      case OP_CALL: case OP_TAILCALL:
        return getobjname(L, (func+1)+GETARG_A(i), name);
      default:
        return NULL;
    }
  }
}
