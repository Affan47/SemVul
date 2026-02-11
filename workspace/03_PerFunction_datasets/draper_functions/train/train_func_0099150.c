output_50 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{

{
  if (find_reg_note (insn, REG_UNUSED, operands[3]))
    return "divxs.b\t%X2,%T0";
  else
    return "divxs.b\t%X2,%T0\n\tmov.b\t%t0,%s3";
}
}
