getIntegerValue(long min,
				  long max) 		const
{
  long value = std::atol(fValue.c_str());

  if(value > max)
    value = max;
  else if(value < min)
    value = min;

  return value;
}
