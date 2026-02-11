emit_cmp_and_jump_insns (rtx x, rtx y, enum rtx_code comparison, rtx size,
			 enum machine_mode mode, int unsignedp, rtx label)
{
  rtx op0 = x, op1 = y;
  rtx test;


  if (swap_commutative_operands_p (x, y)
      && can_compare_p (swap_condition (comparison), mode, ccp_jump))
    {
      op0 = y, op1 = x;
      comparison = swap_condition (comparison);
    }


  if (CONSTANT_P (op0))
    op0 = force_reg (mode, op0);

  if (unsignedp)
    comparison = unsigned_condition (comparison);

  prepare_cmp_insn (op0, op1, comparison, size, unsignedp, OPTAB_LIB_WIDEN,
		    &test, &mode);
  emit_cmp_and_jump_insn_1 (test, mode, label);
}
