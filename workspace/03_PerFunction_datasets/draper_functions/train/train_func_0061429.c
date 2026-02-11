gen_split_2439 (rtx curr_insn ATTRIBUTE_UNUSED, rtx *operands)
{
  rtx operand0;
  rtx operand1;
  rtx operand2;
  rtx operand3;
  rtx operand4;
  rtx operand5;
  rtx _val = 0;
  start_sequence ();
#line 7341 "../../src/gcc/config/i386/i386.md"
{
  operands[5] = GEN_INT (GET_MODE_BITSIZE (SImode)-1);

  if (SImode != HImode
      && (optimize_function_for_size_p (cfun) || TARGET_USE_CLTD))
    operands[4] = operands[2];
  else
    {

      emit_move_insn (operands[1], operands[2]);
      operands[4] = operands[1];
    }
}
  operand0 = operands[0];
  (void) operand0;
  operand1 = operands[1];
  (void) operand1;
  operand2 = operands[2];
  (void) operand2;
  operand3 = operands[3];
  (void) operand3;
  operand4 = operands[4];
  (void) operand4;
  operand5 = operands[5];
  (void) operand5;
  emit (gen_rtx_PARALLEL (VOIDmode,
	gen_rtvec (2,
		gen_rtx_SET (VOIDmode,
	operand1,
	gen_rtx_ASHIFTRT (SImode,
	operand4,
	operand5)),
		gen_hard_reg_clobber (CCmode, 17))));
  emit (gen_rtx_PARALLEL (VOIDmode,
	gen_rtvec (4,
		gen_rtx_SET (VOIDmode,
	operand0,
	gen_rtx_DIV (SImode,
	operand2,
	operand3)),
		gen_rtx_SET (VOIDmode,
	copy_rtx (operand1),
	gen_rtx_MOD (SImode,
	copy_rtx (operand2),
	copy_rtx (operand3))),
		gen_rtx_USE (VOIDmode,
	copy_rtx (operand1)),
		gen_hard_reg_clobber (CCmode, 17))));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
