di_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case CONST_INT:
    case CONST_DOUBLE:
      return true;
    default:
      break;
    }
  return (GET_CODE (op) == REG || GET_CODE (op) == SUBREG || GET_CODE (op) == MEM) && (nonimmediate_di_operand (op, mode));
}
