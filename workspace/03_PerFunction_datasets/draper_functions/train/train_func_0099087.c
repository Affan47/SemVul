Un_Number_Check(double value, WamWord start_word)
{
  long n;

  CHECK_FOR_UN_NUMBER;

  n = (long) value;

  return (n == value) ? Get_Integer(n, word) : Get_Float(value, word);
}
