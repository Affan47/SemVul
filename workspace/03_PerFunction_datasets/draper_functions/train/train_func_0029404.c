bit_works_highest_bit_set_8_test (void)
{
  g_assert(0x00 == bit_works_highest_bit_set_8(0x00));
  g_assert(0x01 == bit_works_highest_bit_set_8(0x01));
  g_assert(0x02 == bit_works_highest_bit_set_8(0x02));
  g_assert(0x02 == bit_works_highest_bit_set_8(0x03));
  g_assert(0x80 == bit_works_highest_bit_set_8(0xFF));
}
