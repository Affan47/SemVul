thumb2_index_mul_operand (rtx op)
{
  HOST_WIDE_INT val;

  if (GET_CODE(op) != CONST_INT)
    return false;

  val = INTVAL(op);
  return (val == 1 || val == 2 || val == 4 || val == 8);
}
