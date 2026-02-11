gen_rdpmc (rtx operand0,
	rtx operand1)
{
  rtx _val = 0;
  start_sequence ();
  {
    rtx operands[2];
    operands[0] = operand0;
    operands[1] = operand1;
#line 18059 "../../src/gcc/config/i386/i386.md"
{
  rtx reg = gen_reg_rtx (DImode);
  rtx si;


  rtx ecx = gen_rtx_REG (SImode, CX_REG);
  emit_insn (gen_rtx_SET (VOIDmode, ecx, operands[1]));
  si = gen_rtx_UNSPEC_VOLATILE (DImode, gen_rtvec (1, ecx),
				UNSPECV_RDPMC);

  if (TARGET_64BIT)
    {
      rtvec vec = rtvec_alloc (2);
      rtx load = gen_rtx_PARALLEL (VOIDmode, vec);
      rtx upper = gen_reg_rtx (DImode);
      rtx di = gen_rtx_UNSPEC_VOLATILE (DImode,
					gen_rtvec (1, const0_rtx),
					UNSPECV_RDPMC);
      RTVEC_ELT (vec, 0) = gen_rtx_SET (VOIDmode, reg, si);
      RTVEC_ELT (vec, 1) = gen_rtx_SET (VOIDmode, upper, di);
      emit_insn (load);
      upper = expand_simple_binop (DImode, ASHIFT, upper, GEN_INT (32),
				   NULL, 1, OPTAB_DIRECT);
      reg = expand_simple_binop (DImode, IOR, reg, upper, reg, 1,
				 OPTAB_DIRECT);
    }
  else
    emit_insn (gen_rtx_SET (VOIDmode, reg, si));
  emit_insn (gen_rtx_SET (VOIDmode, operands[0], reg));
  DONE;
}
    operand0 = operands[0];
    (void) operand0;
    operand1 = operands[1];
    (void) operand1;
  }
  emit (operand0);
  emit (operand1);
  _val = get_insns ();
  end_sequence ();
  return _val;
}
