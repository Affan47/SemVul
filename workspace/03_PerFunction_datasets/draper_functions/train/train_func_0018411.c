rtx_addr_can_trap_p (x)
     rtx x;
{
  enum rtx_code code = GET_CODE (x);

  switch (code)
    {
    case SYMBOL_REF:
      return SYMBOL_REF_WEAK (x);

    case LABEL_REF:
      return 0;

    case REG:

      if (x == frame_pointer_rtx || x == hard_frame_pointer_rtx
	  || x == stack_pointer_rtx

	  || (x == arg_pointer_rtx && fixed_regs[ARG_POINTER_REGNUM]))
	return 0;

      if (REGNO (x) >= FIRST_VIRTUAL_REGISTER
	  && REGNO (x) <= LAST_VIRTUAL_REGISTER)
	return 0;
      return 1;

    case CONST:
      return rtx_addr_can_trap_p (XEXP (x, 0));

    case PLUS:


      return ! ((! rtx_addr_can_trap_p (XEXP (x, 0))
		 && GET_CODE (XEXP (x, 1)) == CONST_INT)
		|| (XEXP (x, 0) == pic_offset_table_rtx
		    && CONSTANT_P (XEXP (x, 1))));

    case LO_SUM:
    case PRE_MODIFY:
      return rtx_addr_can_trap_p (XEXP (x, 1));

    case PRE_DEC:
    case PRE_INC:
    case POST_DEC:
    case POST_INC:
    case POST_MODIFY:
      return rtx_addr_can_trap_p (XEXP (x, 0));

    default:
      break;
    }


  return 1;
}
