getfuncname (lua_State *L, CallInfo *ci, const char **name) {
  TMS tm;
  Proto *p = ci_func(ci)->p;
  int pc = currentpc(ci);
  Instruction i = p->code[pc];
  switch (GET_OPCODE(i)) {
    case OP_CALL:
    case OP_TAILCALL:
      return getobjname(p, pc, GETARG_A(i), name);
    case OP_TFORCALL: {
      *name = "for iterator";
       return "for iterator";
    }

    case OP_SELF:
    case OP_GETTABUP:
    case OP_GETTABLE: tm = TM_INDEX; break;
    case OP_SETTABUP:
    case OP_SETTABLE: tm = TM_NEWINDEX; break;
    case OP_EQ: tm = TM_EQ; break;
    case OP_ADD: tm = TM_ADD; break;
    case OP_SUB: tm = TM_SUB; break;
    case OP_MUL: tm = TM_MUL; break;
    case OP_DIV: tm = TM_DIV; break;
    case OP_MOD: tm = TM_MOD; break;
    case OP_POW: tm = TM_POW; break;
    case OP_UNM: tm = TM_UNM; break;
    case OP_LEN: tm = TM_LEN; break;
    case OP_LT: tm = TM_LT; break;
    case OP_LE: tm = TM_LE; break;
    case OP_CONCAT: tm = TM_CONCAT; break;
    default:
      return NULL;
  }
  *name = getstr(G(L)->tmname[tm]);
  return "metamethod";
}
