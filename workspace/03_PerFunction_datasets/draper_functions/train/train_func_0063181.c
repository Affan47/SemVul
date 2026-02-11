safe_vector_operand (rtx x, enum machine_mode mode)
{
  if (x != const0_rtx)
    return x;
  x = gen_reg_rtx (mode);

  emit_insn (gen_iwmmxt_clrdi (mode == DImode ? x
			       : gen_rtx_SUBREG (DImode, x, 0)));
  return x;
}
