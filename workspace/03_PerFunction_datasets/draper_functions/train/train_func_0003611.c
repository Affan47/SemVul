gen_vsx_xxpermdi_v2df (rtx operand0,
	rtx operand1,
	rtx operand2,
	rtx operand3)
{
  rtx _val = 0;
  start_sequence ();
  {
    rtx operands[4];
    operands[0] = operand0;
    operands[1] = operand1;
    operands[2] = operand2;
    operands[3] = operand3;
#line 1625 "../../src/gcc/config/rs6000/vsx.md"
{
  rtx target = operands[0];
  rtx op0 = operands[1];
  rtx op1 = operands[2];
  int mask = INTVAL (operands[3]);
  rtx perm0 = GEN_INT ((mask >> 1) & 1);
  rtx perm1 = GEN_INT ((mask & 1) + 2);
  rtx (*gen) (rtx, rtx, rtx, rtx, rtx);

  if (V2DFmode == V2DFmode)
    gen = gen_vsx_xxpermdi2_v2df_1;
  else
    {
      gen = gen_vsx_xxpermdi2_v2di_1;
      if (V2DFmode != V2DImode)
	{
	  target = gen_lowpart (V2DImode, target);
	  op0 = gen_lowpart (V2DImode, op0);
	  op1 = gen_lowpart (V2DImode, op1);
	}
    }


  if (BYTES_BIG_ENDIAN)
    emit_insn (gen (target, op0, op1, perm0, perm1));
  else
    {
      rtx p0 = GEN_INT (3 - INTVAL (perm1));
      rtx p1 = GEN_INT (3 - INTVAL (perm0));
      emit_insn (gen (target, op1, op0, p0, p1));
    }
  DONE;
}
    operand0 = operands[0];
    (void) operand0;
    operand1 = operands[1];
    (void) operand1;
    operand2 = operands[2];
    (void) operand2;
    operand3 = operands[3];
    (void) operand3;
  }
  emit (operand0);
  emit (operand1);
  emit (operand2);
  emit (operand3);
  _val = get_insns ();
  end_sequence ();
  return _val;
}
