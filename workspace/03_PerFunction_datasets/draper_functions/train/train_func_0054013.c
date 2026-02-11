compress_float_constant (rtx x, rtx y)
{
  enum machine_mode dstmode = GET_MODE (x);
  enum machine_mode orig_srcmode = GET_MODE (y);
  enum machine_mode srcmode;
  REAL_VALUE_TYPE r;

  REAL_VALUE_FROM_CONST_DOUBLE (r, y);

  for (srcmode = GET_CLASS_NARROWEST_MODE (GET_MODE_CLASS (orig_srcmode));
       srcmode != orig_srcmode;
       srcmode = GET_MODE_WIDER_MODE (srcmode))
    {
      enum insn_code ic;
      rtx trunc_y, last_insn;


      ic = can_extend_p (dstmode, srcmode, 0);
      if (ic == CODE_FOR_nothing)
	continue;


      if (! exact_real_truncate (srcmode, &r))
	continue;

      trunc_y = CONST_DOUBLE_FROM_REAL_VALUE (r, srcmode);

      if (LEGITIMATE_CONSTANT_P (trunc_y))
	{


	  if (! (*insn_data[ic].operand[1].predicate) (trunc_y, srcmode))
	    continue;
	}
      else if (float_extend_from_mem[dstmode][srcmode])
	trunc_y = validize_mem (force_const_mem (srcmode, trunc_y));
      else
	continue;

      emit_unop_insn (ic, x, trunc_y, UNKNOWN);
      last_insn = get_last_insn ();

      if (GET_CODE (x) == REG)
	set_unique_reg_note (last_insn, REG_EQUAL, y);

      return last_insn;
    }

  return NULL_RTX;
}
