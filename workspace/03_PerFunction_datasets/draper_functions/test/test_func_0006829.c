field_is1(const elem_t x)
{
  int i;
  if (*x++ != 1) return 0;
  for(i = 1; i < NUMWORDS && ! *x++; i++);
  return i == NUMWORDS;
}
