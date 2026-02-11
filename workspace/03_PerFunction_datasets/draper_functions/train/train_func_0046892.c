_nrrdTernaryOpMin(double a, double b, double c) {
  b = AIR_MIN(b, c);
  return AIR_MIN(a, b);
}
