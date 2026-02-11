whole_digit_count( double value)
{
  int digits = 1;
  double dummy;

  for(dummy = value;
      GREATER_THAN_OR_TOLERABLY_EQUAL(dummy,10,TOLERANCE);
      dummy /= 10) {
    digits++;
  }

  return digits;
}
