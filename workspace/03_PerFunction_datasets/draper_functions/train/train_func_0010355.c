EqString (
    Obj                 listL,
    Obj                 listR )
{
  UInt lL, lR, i;
  UInt1 *pL, *pR;
  lL = GET_LEN_STRING(listL);
  lR = GET_LEN_STRING(listR);
  if (lR != lL) return 0;
  pL = CHARS_STRING(listL);
  pR = CHARS_STRING(listR);
  for (i=0; i<lL && pL[i] == pR[i]; i++);
  return (i == lL);
}
