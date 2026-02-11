gl_regioncode (CONST int x, CONST int y)
{
  int             result = 0;
  if (x < 0)
    result |= 1;
  else if (x > __clipx2)
    result |= 2;
  if (y < 0)
    result |= 4;
  else if (y > __clipy2)
    result |= 8;
  return result;
}
