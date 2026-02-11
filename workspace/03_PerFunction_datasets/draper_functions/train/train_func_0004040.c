_dmalloc_rand(void)
{
  if (value == 0) {
    auto_seed();
  }


  value = MAGIC_A * (value % MAGIC_QUOTIENT) -
    MAGIC_REMAINDER * (value / MAGIC_QUOTIENT);

  if (value <= 0) {
    value += MERSENNE_PRIME;
  }

  return value;
}
