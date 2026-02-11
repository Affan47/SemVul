arm_expand_binop_builtin (enum insn_code icode,
			  tree exp, rtx target, bool allow_void)
{
  rtx pat;
  tree arg0 = CALL_EXPR_ARG (exp, 0);
  tree arg1 = CALL_EXPR_ARG (exp, 1);
  rtx op0 = expand_normal (arg0);
  rtx op1 = expand_normal (arg1);
  enum machine_mode tmode = insn_data[icode].operand[0].mode;
  enum machine_mode mode0 = insn_data[icode].operand[1].mode;
  enum machine_mode mode1 = insn_data[icode].operand[2].mode;

  if (VECTOR_MODE_P (mode0))
    op0 = safe_vector_operand (op0, mode0);
  if (VECTOR_MODE_P (mode1))
    op1 = safe_vector_operand (op1, mode1);

  if (! target
      || GET_MODE (target) != tmode
      || ! (*insn_data[icode].operand[0].predicate) (target, tmode))
    target = gen_reg_rtx (tmode);

  if (GET_MODE (op0) != mode0)
    {
      error ("the first argument to the builtin has mode %s, expecting %s",
	     mode_name[GET_MODE (op0)], mode_name[mode0]);


      return const0_rtx;
    }

  if (GET_MODE (op1) != mode1)
    {
      if (GET_MODE (op1) == VOIDmode)
	{


	  if (! allow_void)
	    op1 = copy_to_mode_reg (mode1, op1);
	}
      else
	{
	  error ("the second argument to the builtin has mode %s, expecting %s",
		 mode_name[GET_MODE (op1)], mode_name[mode1]);
	  return const0_rtx;
	}
    }

  if (! (*insn_data[icode].operand[1].predicate) (op0, mode0))
    op0 = copy_to_mode_reg (mode0, op0);
  if (! (*insn_data[icode].operand[2].predicate) (op1, mode1))
    op1 = copy_to_mode_reg (mode1, op1);

  pat = GEN_FCN (icode) (target, op0, op1);
  if (! pat)
    return 0;
  emit_insn (pat);
  return target;
}
