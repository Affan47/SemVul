general_constant_p (rtx x)
{
  return CONSTANT_P (x) && (! flag_pic || LEGITIMATE_PIC_OPERAND_P (x));
}
