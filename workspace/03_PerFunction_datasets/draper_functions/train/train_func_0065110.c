inbounds (aMin, aMax, aValue)
  long aMin, aMax, aValue;
{
  if ((aValue >= aMin) && (aValue <= aMax)) return (F_MIN_IN);

  if (aValue < aMin) return (F_MIN_LOWER);

  return (F_MIN_GREATER);
}
