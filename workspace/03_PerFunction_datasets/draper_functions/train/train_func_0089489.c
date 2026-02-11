GetPrice(bool matchMode, Byte matchByte, Byte symbol) const
{
  UInt32 price = 0;
  UInt32 context = 1;
  int i = 8;
  if (matchMode)
  {
    do
    {
      i--;
      UInt32 matchBit = (matchByte >> i) & 1;
      UInt32 bit = (symbol >> i) & 1;
      price += _encoders[0x100 + (matchBit << 8) + context].GetPrice(bit);
      context = (context << 1) | bit;
      if (matchBit != bit)
        break;
    }
    while (i != 0);
  }
  while(i != 0)
  {
    i--;
    UInt32 bit = (symbol >> i) & 1;
    price += _encoders[context].GetPrice(bit);
    context = (context << 1) | bit;
  }
  return price;
}
