gen_split_2648 (rtx curr_insn ATTRIBUTE_UNUSED, rtx *operands ATTRIBUTE_UNUSED)
{
  rtx _val = 0;
  start_sequence ();
#line 1862 "../../src/gcc/config/rs6000/vsx.md"

{
  rtx tmp = (GET_CODE (operands[2]) == SCRATCH)
	     ? gen_reg_rtx (V2DFmode)
	     : operands[2];
  emit_insn (gen_vsx_xxsldwi_v2df (tmp, operands[1], operands[1], const2_rtx));
  emit_insn (gen_addv2df3 (operands[0], tmp, operands[1]));
  DONE;
}
  emit_insn (const0_rtx);
  _val = get_insns ();
  end_sequence ();
  return _val;
}
