setMathDisplayMode(Symbol sym)
{
  switch (sym) {
  case symbolDisplay:
    specFormat_.mathInline = 0;
    break;
  case symbolInline:
    specFormat_.mathInline = 1;
    break;
  default:
    break;
  }
}
