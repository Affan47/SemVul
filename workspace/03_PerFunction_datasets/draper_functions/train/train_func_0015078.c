bit_works_type_size_test (void)
{
  g_assert(8 == sizeof(uint64_t));
  g_assert(4 == sizeof(uint32_t));
  g_assert(1 == sizeof(uint8_t));
}
