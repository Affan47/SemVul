mtwist_update_state(mtwist* mt)
{
  int count;
  uint32_t *p = mt->state;

  for(count = (MTWIST_N - MTWIST_M + 1); --count; p++)
    *p = p[MTWIST_M] ^ MTWIST_TWIST(p[0], p[1]);

  for(count = MTWIST_M; --count; p++)
    *p = p[MTWIST_M - MTWIST_N] ^ MTWIST_TWIST(p[0], p[1]);

  *p = p[MTWIST_M - MTWIST_N] ^ MTWIST_TWIST(p[0], mt->state[0]);

  mt->remaining = MTWIST_N;
  mt->next = mt->state;
}
