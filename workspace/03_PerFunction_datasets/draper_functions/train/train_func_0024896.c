m68hc11_small_indexed_indirect_p (operand, mode)
     rtx operand;
     enum machine_mode mode;
{
  rtx base, offset;
  int addr_mode;

  if (GET_CODE (operand) == REG && reload_in_progress
      && REGNO (operand) >= FIRST_PSEUDO_REGISTER
      && reg_equiv_memory_loc[REGNO (operand)])
    {
      operand = reg_equiv_memory_loc[REGNO (operand)];
      operand = eliminate_regs (operand, 0, NULL_RTX);
    }

  if (GET_CODE (operand) != MEM)
    return 0;

  operand = XEXP (operand, 0);
  if (CONSTANT_ADDRESS_P (operand))
    return 1;

  if (PUSH_POP_ADDRESS_P (operand))
    return 1;

  addr_mode = m68hc11_mov_addr_mode | (reload_completed ? ADDR_STRICT : 0);
  if (!register_indirect_p (operand, mode, addr_mode))
    return 0;

  if (TARGET_M6812 && GET_CODE (operand) == PLUS
      && (reload_completed | reload_in_progress))
    {
      base = XEXP (operand, 0);
      offset = XEXP (operand, 1);


      if (GET_CODE (base) != CONST_INT && GET_CODE (offset) != CONST_INT)
        return 0;

      if (GET_CODE (base) == CONST_INT)
	offset = base;

      switch (GET_MODE_SIZE (mode))
	{
	case 8:
	  if (INTVAL (offset) < -16 + 6 || INTVAL (offset) > 15 - 6)
	    return 0;
	  break;

	case 4:
	  if (INTVAL (offset) < -16 + 2 || INTVAL (offset) > 15 - 2)
	    return 0;
	  break;

	default:
	  if (INTVAL (offset) < -16 || INTVAL (offset) > 15)
	    return 0;
	  break;
	}
    }
  return 1;
}
