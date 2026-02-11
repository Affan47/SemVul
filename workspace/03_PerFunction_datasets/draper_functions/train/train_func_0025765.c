getAsInteger(unsigned Radix, unsigned &Result) const {
  unsigned long long Val;
  if (getAsInteger(Radix, Val) ||
      (unsigned)Val != Val)
    return true;
  Result = Val;
  return false;
}
