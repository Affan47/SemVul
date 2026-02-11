InChIErrorMessage(const char ch)
{
  string s;
  switch (ch)
  {
  case 0:
    s = " are identical";
    break;
  case '+':
    s = " have different formulae";
    break;
  case 'c':
    s = " have different connection tables";
    break;
  case 'h':
    s = " have different bond orders, or radical character";
    break;
  case 'q':
    s = " have different charges";
    break;
  case 'p':
    s = " have different numbers of attached protons";
    break;
  case 'b':
    s = " have different double bond stereochemistry";
    break;
  case 'm':
  case 't':
    s = " have different sp3 stereochemistry";
    break;
  case 'i':
    s = " have different isotopic composition";
    break;
  default:
    s = " are different";
  }
  return s;
}
