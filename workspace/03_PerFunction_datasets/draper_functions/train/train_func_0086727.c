init_genrand( rng_state_t *state, uint32_t s )
{
  state->mt[0]= s & 0xffffffffUL;
  for (state->mti=1; state->mti<N; state->mti++) {
    state->mt[state->mti] =
      (1812433253UL * (state->mt[state->mti-1]
		       ^ (state->mt[state->mti-1] >> 30))
       + state->mti);


  }
}
