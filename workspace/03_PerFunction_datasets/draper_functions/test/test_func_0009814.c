terminator(const uchar *ptr,uint length)
{
  int chr=0;
  uint i;
  for (i=1 ; i < length ; i++)
  {
    if ((chr=GET) != *++ptr)
    {
      break;
    }
  }
  if (i == length)
    return 1;
  PUSH(chr);
  while (i-- > 1)
    PUSH(*--ptr);
  return 0;
}
