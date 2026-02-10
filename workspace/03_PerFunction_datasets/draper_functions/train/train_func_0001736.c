lock_ool(volatile AO_TS_t *l)
{
  int i = 0;

  while (AO_test_and_set_acquire(l) == AO_TS_SET)
    AO_pause(++i);
}
