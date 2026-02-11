random(unsigned long limit_)
{
  if (_useDefaultGen==MSTrue)
    {
      MSGUARD(defaultGenMutex);
      return defaultGen().random(limit_);
    }
  else
    {
      _seed=_seed*5709421UL+1UL;
      return ((_seed>>16)%limit_);
    }
}
