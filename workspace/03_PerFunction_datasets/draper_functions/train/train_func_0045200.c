convertDigit(Xchar c, int &weight)
{
  static const char digits[] = "0123456789";
  for (int i = 0; digits[i] != '\0'; i++)
    if (matchChar(c, digits[i])) {
      weight = i;
      return 1;
    }
  return 0;
}
