gen_tls_global_dynamic_32 (rtx operand0,
	rtx operand1)
{
  rtx operand2;
  rtx operand3;
  rtx operand4 ATTRIBUTE_UNUSED;
  rtx operand5 ATTRIBUTE_UNUSED;
  rtx _val = 0;
  start_sequence ();
  {
    rtx operands[6];
    operands[0] = operand0;
    operands[1] = operand1;
#line 12559 "../../src/gcc/config/i386/i386.md"
{
  if (flag_pic)
    operands[2] = pic_offset_table_rtx;
  else
    {
      operands[2] = gen_reg_rtx (Pmode);
      emit_insn (gen_set_got (operands[2]));
    }
  if (TARGET_GNU2_TLS)
    {
       emit_insn (gen_tls_dynamic_gnu2_32
		  (operands[0], operands[1], operands[2]));
       DONE;
    }
  operands[3] = ix86_tls_get_addr ();
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
  }
  emit (gen_rtx_PARALLEL (VOIDmode,
	gen_rtvec (4,
		gen_rtx_SET (VOIDmode,
	operand0,
	gen_rtx_UNSPEC (SImode,
	gen_rtvec (3,
		operand2,
		operand1,
		operand3),
	21)),
		gen_rtx_CLOBBER (VOIDmode,
	gen_rtx_SCRATCH (SImode)),
		gen_rtx_CLOBBER (VOIDmode,
	gen_rtx_SCRATCH (SImode)),
		gen_hard_reg_clobber (CCmode, 17))));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
