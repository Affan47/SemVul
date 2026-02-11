uniq_sort_alt_states (alt_state_t alt_states_list)
{
  alt_state_t curr_alt_state;
  VEC(alt_state_t, heap) *alt_states;
  size_t i;
  size_t prev_unique_state_ind;
  alt_state_t result;

  if (alt_states_list == 0)
    return 0;
  if (alt_states_list->next_alt_state == 0)
    return alt_states_list;

  alt_states = VEC_alloc (alt_state_t, heap, 150);
  for (curr_alt_state = alt_states_list;
       curr_alt_state != NULL;
       curr_alt_state = curr_alt_state->next_alt_state)
    VEC_safe_push (alt_state_t, heap, alt_states, curr_alt_state);

  VEC_qsort (alt_state_t, alt_states, alt_state_cmp);

  prev_unique_state_ind = 0;
  for (i = 1; i < VEC_length (alt_state_t, alt_states); i++)
    if (VEC_index (alt_state_t, alt_states, prev_unique_state_ind)->state
	!= VEC_index (alt_state_t, alt_states, i)->state)
      {
	prev_unique_state_ind++;
	VEC_replace (alt_state_t, alt_states, prev_unique_state_ind,
		     VEC_index (alt_state_t, alt_states, i));
      }
  VEC_truncate (alt_state_t, alt_states, prev_unique_state_ind + 1);

  for (i = 1; i < VEC_length (alt_state_t, alt_states); i++)
    VEC_index (alt_state_t, alt_states, i-1)->next_sorted_alt_state
      = VEC_index (alt_state_t, alt_states, i);
  VEC_last (alt_state_t, alt_states)->next_sorted_alt_state = 0;

  result = VEC_index (alt_state_t, alt_states, 0);

  VEC_free (alt_state_t, heap, alt_states);
  return result;
}
