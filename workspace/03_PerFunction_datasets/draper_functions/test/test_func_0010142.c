test_flip_bit(MY_BITMAP *map, uint bitsize)
{
  uint i, test_bit;
  uint no_loops= bitsize > 128 ? 128 : bitsize;
  for (i=0; i < no_loops; i++)
  {
    test_bit= get_rand_bit(bitsize);
    bitmap_flip_bit(map, test_bit);
    if (!bitmap_is_set(map, test_bit))
      goto error1;
    bitmap_flip_bit(map, test_bit);
    if (bitmap_is_set(map, test_bit))
      goto error2;
  }
  return FALSE;
error1:
  printf("Error in flip bit 1, bit %u, bitsize = %u", test_bit, bitsize);
  return TRUE;
error2:
  printf("Error in flip bit 2, bit %u, bitsize = %u", test_bit, bitsize);
  return TRUE;
}
