m68hc11_auto_inc_p (x)
     rtx x;
{
  return GET_CODE (x) == PRE_DEC
    || GET_CODE (x) == POST_INC
    || GET_CODE (x) == POST_DEC || GET_CODE (x) == PRE_INC;
}
