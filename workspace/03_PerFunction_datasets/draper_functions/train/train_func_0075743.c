ix86_comparison_int_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case NE:
    case EQ:
    case GE:
    case GT:
    case LE:
    case LT:
      break;
    default:
      return false;
    }
  return
(mode == VOIDmode || GET_MODE (op) == mode);
}
