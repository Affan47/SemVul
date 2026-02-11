valid_initial_value_p (rtx x, rtx insn, int call_seen, rtx loop_start)
{
  if (CONSTANT_P (x))
    return 1;


  if (GET_CODE (x) != REG
      || REGNO (x) >= max_reg_before_loop)
    return 0;


  if (REGNO (x) < FIRST_PSEUDO_REGISTER
      && (SMALL_REGISTER_CLASSES
	  || (call_used_regs[REGNO (x)] && call_seen)))
    return 0;


  if (reg_set_between_p (x, insn, loop_start))
    return 0;

  return 1;
}
