cprop_constant_p (const_rtx x)
{
  return CONSTANT_P (x) && (GET_CODE (x) != CONST || shared_const_p (x));
}
