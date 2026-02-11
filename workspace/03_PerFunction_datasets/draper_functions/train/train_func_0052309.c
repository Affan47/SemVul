gg_set_rand_state(struct gg_rand_state *state)
{
  int i;
  for (i = 0; i < N; i++)
    x[i] = state->x[i];
  k = state->k;
}
