init_by_array( rng_state_t *state, uint32_t init_key[], int key_length )
{
  int i, j, k;

  init_genrand(state, 19650218UL);
  i=1; j=0;
  k = (N>key_length ? N : key_length);
  for (; k; k--) {
    state->mt[i] = ( state->mt[i]
		     ^ ( ( state->mt[i-1] ^ ( state->mt[i-1] >> 30 ) )
			 * 1664525UL ) )
      + init_key[j] + j;
    i++; j++;
    if (i>=N) { state->mt[0] = state->mt[N-1]; i=1; }
    if (j>=key_length) j=0;
  }
  for (k=N-1; k; k--) {
    state->mt[i] = ( state->mt[i]
		     ^ ( ( state->mt[i-1] ^ ( state->mt[i-1] >> 30 ) )
			 * 1566083941UL ) )
      - i;
    state->mt[i] &= 0xffffffffUL;
    i++;
    if (i>=N) { state->mt[0] = state->mt[N-1]; i=1; }
  }

  state->mt[0]|= 0x80000000UL;
}
