bit_works_bitscan_MS1B_to_base8_test (void)
{
  HiLo ret;
  uint64_t bit_sequence;

  ret = (HiLo) { .hi = 0, .lo = 0 };
  bit_sequence = 1ULL << 0;
  bit_works_bitscan_MS1B_to_base8 (&ret, bit_sequence);
  g_assert((0 == ret.hi) && (0 == ret.lo));

  ret = (HiLo) { .hi = 0, .lo = 0 };
  bit_sequence = 1ULL << 1;
  bit_works_bitscan_MS1B_to_base8 (&ret, bit_sequence);
  g_assert((0 == ret.hi) && (1 == ret.lo));

  ret = (HiLo) { .hi = 0, .lo = 0 };
  bit_sequence = 1ULL << 7;
  bit_works_bitscan_MS1B_to_base8 (&ret, bit_sequence);
  g_assert((0 == ret.hi) && (7 == ret.lo));

  ret = (HiLo) { .hi = 0, .lo = 0 };
  bit_sequence = 1ULL << 8;
  bit_works_bitscan_MS1B_to_base8 (&ret, bit_sequence);
  g_assert((1 == ret.hi) && (0 == ret.lo));

  ret = (HiLo) { .hi = 0, .lo = 0 };
  bit_sequence = 1ULL << 63;
  bit_works_bitscan_MS1B_to_base8 (&ret, bit_sequence);
  g_assert((7 == ret.hi) && (7 == ret.lo));

}
