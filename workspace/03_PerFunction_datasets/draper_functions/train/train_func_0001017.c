test_container_bitarray(void)
{
  bitarray_t *ba = NULL;
  int i, j, ok=1;

  ba = bitarray_init_zero(1);
  test_assert(ba);
  test_assert(! bitarray_is_set(ba, 0));
  bitarray_set(ba, 0);
  test_assert(bitarray_is_set(ba, 0));
  bitarray_clear(ba, 0);
  test_assert(! bitarray_is_set(ba, 0));
  bitarray_free(ba);

  ba = bitarray_init_zero(1023);
  for (i = 1; i < 64; ) {
    for (j = 0; j < 1023; ++j) {
      if (j % i)
        bitarray_set(ba, j);
      else
        bitarray_clear(ba, j);
    }
    for (j = 0; j < 1023; ++j) {
      if (!bool_eq(bitarray_is_set(ba, j), j%i))
        ok = 0;
    }
    test_assert(ok);
    if (i < 7)
      ++i;
    else if (i == 28)
      i = 32;
    else
      i += 7;
  }

 done:
  if (ba)
    bitarray_free(ba);
}
