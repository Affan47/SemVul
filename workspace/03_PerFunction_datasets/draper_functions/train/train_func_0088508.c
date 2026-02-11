commutative_operand_precedence (rtx op)
{

  if (GET_CODE (op) == CONST_INT)
    return -5;
  if (GET_CODE (op) == CONST_DOUBLE)
    return -4;
  if (CONSTANT_P (op))
    return -3;


  if (GET_CODE (op) == SUBREG
      && GET_RTX_CLASS (GET_CODE (SUBREG_REG (op))) == 'o')
    return -2;


  if (GET_CODE (op) == NEG || GET_CODE (op) == NOT
      || GET_CODE (op) == MULT || GET_CODE (op) == PLUS
      || GET_CODE (op) == MINUS)
    return 2;


  if (GET_RTX_CLASS (GET_CODE (op)) == 'o')
    return -1;
  return 0;
}
