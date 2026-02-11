getInteger(unsigned short length)
{
  unsigned long result = 0;
  for (unsigned short i = 0; i < length; ++i)
    result |= (getBit() << i);
  return result;
}
