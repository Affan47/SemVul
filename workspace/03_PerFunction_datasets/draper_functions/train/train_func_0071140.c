add_state_reservs (state_t state)
{
  alt_state_t curr_alt_state;

  if (state->component_states != NULL)
    for (curr_alt_state = state->component_states;
         curr_alt_state != NULL;
         curr_alt_state = curr_alt_state->next_sorted_alt_state)
      add_state_reservs (curr_alt_state->state);
  else
    VEC_safe_push (reserv_sets_t, heap, state_reservs, state->reservs);
}
