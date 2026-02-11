uni32_get (void *vstate)
{
  uni32_state_t *state = (uni32_state_t *) vstate;
  const long int i = state->i;
  const long int j = state->j;


  long int k = state->m[i] - state->m[j];

  if (k < 0)
    k += m1;
  state->m[j] = k;

  if (i == 0)
    {
      state->i = 16;
    }
  else
    {
      (state->i)--;
    }

  if (j == 0)
    {
      state->j = 16;
    }
  else
    {
      (state->j)--;
    }

  return k;
}
