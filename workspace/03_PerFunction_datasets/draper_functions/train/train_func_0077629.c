arm_thumb_address_cost (rtx x)
{
  enum rtx_code c  = GET_CODE (x);

  if (c == REG)
    return 1;
  if (c == PLUS
      && GET_CODE (XEXP (x, 0)) == REG
      && GET_CODE (XEXP (x, 1)) == CONST_INT)
    return 1;

  return 2;
}
