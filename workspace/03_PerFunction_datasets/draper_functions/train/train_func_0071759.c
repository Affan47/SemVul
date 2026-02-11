SetPrices(UInt32 posState, UInt32 numSymbols, UInt32 *prices) const
{
  UInt32 a0 = _choice.GetPrice0();
  UInt32 a1 = _choice.GetPrice1();
  UInt32 b0 = a1 + _choice2.GetPrice0();
  UInt32 b1 = a1 + _choice2.GetPrice1();
  UInt32 i = 0;
  for (i = 0; i < kNumLowSymbols; i++)
  {
    if (i >= numSymbols)
      return;
    prices[i] = a0 + _lowCoder[posState].GetPrice(i);
  }
  for (; i < kNumLowSymbols + kNumMidSymbols; i++)
  {
    if (i >= numSymbols)
      return;
    prices[i] = b0 + _midCoder[posState].GetPrice(i - kNumLowSymbols);
  }
  for (; i < numSymbols; i++)
    prices[i] = b1 + _highCoder.GetPrice(i - kNumLowSymbols - kNumMidSymbols);
}
