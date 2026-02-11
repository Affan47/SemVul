isShiftedMask(uint64_t I, uint64_t &Pos, uint64_t &Size) {
  if (!isShiftedMask_64(I))
    return false;

  Size = countPopulation(I);
  Pos = countTrailingZeros(I);
  return true;
}
