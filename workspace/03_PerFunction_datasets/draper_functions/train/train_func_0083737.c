xtensa_emit_branch (bool inverted, bool immed, rtx *operands)
{
  static char result[64];
  enum rtx_code code;
  const char *op;

  code = GET_CODE (operands[3]);
  switch (code)
    {
    case EQ:	op = inverted ? "ne" : "eq"; break;
    case NE:	op = inverted ? "eq" : "ne"; break;
    case LT:	op = inverted ? "ge" : "lt"; break;
    case GE:	op = inverted ? "lt" : "ge"; break;
    case LTU:	op = inverted ? "geu" : "ltu"; break;
    case GEU:	op = inverted ? "ltu" : "geu"; break;
    default:	gcc_unreachable ();
    }

  if (immed)
    {
      if (INTVAL (operands[1]) == 0)
	sprintf (result, "b%sz%s\t%%0, %%2", op,
		 (TARGET_DENSITY && (code == EQ || code == NE)) ? ".n" : "");
      else
	sprintf (result, "b%si\t%%0, %%d1, %%2", op);
    }
  else
    sprintf (result, "b%s\t%%0, %%1, %%2", op);

  return result;
}
