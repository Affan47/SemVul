gen_split_2707 (rtx curr_insn ATTRIBUTE_UNUSED, rtx *operands)
{
  rtx operand0;
  rtx operand1;
  rtx operand2;
  rtx operand3;
  rtx operand4;
  rtx _val = 0;
  start_sequence ();
#line 269 "../../src/gcc/config/rs6000/altivec.md"
{
  rtx dup = gen_easy_altivec_constant (operands[1]);
  rtx const_vec;
  enum machine_mode op_mode = TImode;


  XEXP (dup, 0) = simplify_const_binary_operation (ASHIFTRT, QImode,
						   XEXP (dup, 0), const1_rtx);
  const_vec = simplify_rtx (dup);

  if (op_mode == V4SFmode)
    {
      op_mode = V4SImode;
      operands[0] = gen_lowpart (op_mode, operands[0]);
    }
  if (GET_MODE (const_vec) == op_mode)
    operands[3] = const_vec;
  else
    operands[3] = gen_lowpart (op_mode, const_vec);
  operands[4] = gen_rtx_PLUS (op_mode, operands[0], operands[0]);
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
  emit_insn (gen_rtx_SET (VOIDmode,
	operand0,
	operand3));
  emit_insn (gen_rtx_SET (VOIDmode,
	copy_rtx (operand0),
	operand4));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
