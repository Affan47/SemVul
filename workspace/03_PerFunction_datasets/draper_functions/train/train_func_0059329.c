isBasicKind(int kind)
{
  switch (kind) {
    case VARDECLS:
    case LETDECLS:
    case HELP:
    case GET_VALUE:
    case GET_ASSIGNMENT:
    case DUMP_PROOF:
    case DUMP_ASSUMPTIONS:
    case DUMP_SIG:
    case DUMP_TCC:
    case DUMP_TCC_ASSUMPTIONS:
    case DUMP_TCC_PROOF:
    case DUMP_CLOSURE:
    case DUMP_CLOSURE_PROOF:
    case WHERE:
    case ASSERTIONS:
    case ASSUMPTIONS:
    case COUNTEREXAMPLE:
    case COUNTERMODEL:
    case ASSERT:
    case PRINT:
    case QUERY:
    case CHECKSAT:
    case CONTINUE:
    case RESTART:
    case TRACE:
    case ECHO:
    case UNTRACE:
    case VARLIST:
    case FORGET:
    case GET_TYPE:
    case IFF:
    case IMPLIES:
    case TYPEDEF:
    case OPTION:
    case AND:
    case OR:
    case XOR:
    case NOT:
    case DISTINCT:
    case CALL:
    case TRANSFORM:
    case CHECK_TYPE:
    case VARDECL:
    case GET_CHILD:
    case SUBSTITUTE:
    case SEQ:
    case DBG:
    case PUSH:
    case POP:
    case POPTO:
    case PUSH_SCOPE:
    case POP_SCOPE:
    case POPTO_SCOPE:
    case RESET:
    case LETDECL:
    case ELSE:
    case CONTEXT:
      return true;
    default:
      break;
  }
  return false;
}
