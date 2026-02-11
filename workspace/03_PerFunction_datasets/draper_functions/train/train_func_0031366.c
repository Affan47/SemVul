bit_works_bitscan_MS1B_to_base8 (HiLo *result, uint64_t bit_sequence)
{
  uint32_t tmp;
  uint8_t  hi;

  hi = 0;

  if ((bit_sequence & 0xFFFFFFFF00000000) != 0ULL) {
    tmp = (uint32_t) (bit_sequence >> 32);
    hi += 4;
  } else {
    tmp = (uint32_t) bit_sequence;
  }

  if ((tmp & 0xFFFF0000) != 0) {
    tmp >>= 16;
    hi += 2;
  }
  if ((tmp & 0x0000FF00) != 0) {
    tmp >>=  8;
    hi += 1;
  }

  result->hi = hi;
  result->lo = log2_array[tmp];
  return;
}
