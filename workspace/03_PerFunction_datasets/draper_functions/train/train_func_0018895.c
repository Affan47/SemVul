alt_states_eq (alt_state_t alt_states_1, alt_state_t alt_states_2)
{
  while (alt_states_1 != NULL && alt_states_2 != NULL
         && alt_state_cmp (&alt_states_1, &alt_states_2) == 0)
    {
      alt_states_1 = alt_states_1->next_sorted_alt_state;
      alt_states_2 = alt_states_2->next_sorted_alt_state;
    }
  return alt_states_1 == alt_states_2;
}
