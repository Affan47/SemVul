getValueProperty(ExecState *, int token) const
{
  switch (token) {
  case Euler:
    return jsNumber(exp(1.0));
  case Ln2:
    return jsNumber(log(2.0));
  case Ln10:
    return jsNumber(log(10.0));
  case Log2E:
    return jsNumber(1.0/log(2.0));
  case Log10E:
    return jsNumber(1.0/log(10.0));
  case Pi:
    return jsNumber(piDouble);
  case Sqrt1_2:
    return jsNumber(sqrt(0.5));
  case Sqrt2:
    return jsNumber(sqrt(2.0));
  }

  assert(0);
  return 0;
}
