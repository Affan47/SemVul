m68hc11_logical_operator (op, mode)
     register rtx op;
     enum machine_mode mode ATTRIBUTE_UNUSED;
{
  return GET_CODE (op) == AND || GET_CODE (op) == IOR || GET_CODE (op) == XOR;
}
