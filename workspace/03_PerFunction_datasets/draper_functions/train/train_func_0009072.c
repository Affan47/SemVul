safeDiv(uint64_t Numerator, uint64_t Divisor) {
  if (!Numerator)
    return 0;
  return Numerator / Divisor;
}
