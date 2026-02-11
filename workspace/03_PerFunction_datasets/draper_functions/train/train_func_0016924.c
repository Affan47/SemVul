_ds_pow(int base, unsigned int exp) {
  int result = 1;
  while (exp > 0) {
    if (exp & 1)
      result *= base;
    base *= base;
    exp /= 2;
  }
  return result;
}
