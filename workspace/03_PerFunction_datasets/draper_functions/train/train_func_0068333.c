print_exp(Exp* e) {
  switch(e->tag) {
    case EXP_INT:
      fprintf(outfile, "%i", e->u.ival);
      break;
    case EXP_FLOAT:
      fprintf(outfile, "%f", e->u.fval);
      break;
    case EXP_STRING:
      print_string(e->u.sval);
      break;
    case EXP_VAR:
      print_var(e->u.var);
      break;
    case EXP_BINOP:
      {
	fprintf(outfile, "(");
	print_exp(e->u.binop.e1);
	switch(e->u.binop.op) {
	  case TK_EQ: fprintf(outfile, "=="); break;
	  case TK_LEQ: fprintf(outfile, "<="); break;
	  case TK_GEQ: fprintf(outfile, ">="); break;
	  case TK_NEQ: fprintf(outfile, "!="); break;
	  case TK_AND: fprintf(outfile, "&&"); break;
	  case TK_OR: fprintf(outfile, "||"); break;
          default: fprintf(outfile, "%c", e->u.binop.op);
	}
	print_exp(e->u.binop.e2);
	fprintf(outfile, ")");
        break;
      }
    case EXP_NEG:
      {
	fprintf(outfile, "-");
	print_exp(e->u.exp);
	break;
      }
    case EXP_LNEG:
      {
	fprintf(outfile, "!");
	print_exp(e->u.exp);
	break;
      }
     case EXP_FUNCALL:
      {
	fprintf(outfile, "%s(", e->u.funcall.name);
	print_explist(e->u.funcall.expl);
	fprintf(outfile, ")");
      }
  }
}
