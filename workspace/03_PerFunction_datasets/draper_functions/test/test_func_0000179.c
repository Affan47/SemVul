avoid_complex_debug_insns (rtx insn, rtx *exp_p, int depth)
{
  rtx exp = *exp_p;

  if (exp == NULL_RTX)
    return;

  if ((OBJECT_P (exp) && !MEM_P (exp)) || GET_CODE (exp) == CLOBBER)
    return;

  if (depth == 4)
    {

      rtx dval = make_debug_expr_from_rtl (exp);


      rtx bind = gen_rtx_VAR_LOCATION (GET_MODE (exp),
				       DEBUG_EXPR_TREE_DECL (dval), exp,
				       VAR_INIT_STATUS_INITIALIZED);

      emit_debug_insn_before (bind, insn);
      *exp_p = dval;
      return;
    }

  const char *format_ptr = GET_RTX_FORMAT (GET_CODE (exp));
  int i, j;
  for (i = 0; i < GET_RTX_LENGTH (GET_CODE (exp)); i++)
    switch (*format_ptr++)
      {
      case 'e':
	avoid_complex_debug_insns (insn, &XEXP (exp, i), depth + 1);
	break;

      case 'E':
      case 'V':
	for (j = 0; j < XVECLEN (exp, i); j++)
	  avoid_complex_debug_insns (insn, &XVECEXP (exp, i, j), depth + 1);
	break;

      default:
	break;
      }
}
