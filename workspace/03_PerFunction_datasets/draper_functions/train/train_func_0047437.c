remove_state_duplicate_reservs (void)
{
  size_t i, j;

  for (i = 1, j = 0; i < state_reservs.length (); i++)
    if (reserv_sets_cmp (state_reservs[j], state_reservs[i]))
      {
	j++;
	state_reservs[j] = state_reservs[i];
      }
  state_reservs.truncate (j + 1);
}
