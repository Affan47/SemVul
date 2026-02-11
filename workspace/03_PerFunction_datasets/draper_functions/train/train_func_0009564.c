getBaseIdx(double base) {
  int baseIdx;

  baseIdx = (int)(base / textPoolStep);
  if (baseIdx < minBaseIdx) {
    return minBaseIdx;
  }
  if (baseIdx > maxBaseIdx) {
    return maxBaseIdx;
  }
  return baseIdx;
}
