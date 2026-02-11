create_composed_state (original_state, arcs_marked_by_insn, state_stack)
     state_t original_state;
     arc_t arcs_marked_by_insn;
     vla_ptr_t *state_stack;
{
  state_t state;
  alt_state_t curr_alt_state;
  alt_state_t new_alt_state;
  arc_t curr_arc;
  arc_t next_arc;
  state_t state_in_table;
  state_t temp_state;
  alt_state_t canonical_alt_states_list;
  int alts_number;

  if (arcs_marked_by_insn == NULL)
    return;
  if (arcs_marked_by_insn->next_arc_marked_by_insn == NULL)
    state = arcs_marked_by_insn->to_state;
  else
    {
      if (!ndfa_flag)
	abort ();

      state = get_free_state (0, arcs_marked_by_insn->to_state->automaton);
      curr_alt_state = NULL;
      for (curr_arc = arcs_marked_by_insn;
           curr_arc != NULL;
           curr_arc = curr_arc->next_arc_marked_by_insn)
        {
          new_alt_state = get_free_alt_state ();
          new_alt_state->next_alt_state = curr_alt_state;
          new_alt_state->state = curr_arc->to_state;
	  if (curr_arc->to_state->component_states != NULL)
	    abort ();
          curr_alt_state = new_alt_state;
        }

      canonical_alt_states_list = uniq_sort_alt_states (curr_alt_state);
      if (canonical_alt_states_list->next_sorted_alt_state == NULL)
        {
          temp_state = state;
          state = canonical_alt_states_list->state;
          free_state (temp_state);
        }
      else
        {
          state->component_states = canonical_alt_states_list;
          state_in_table = insert_state (state);
          if (state_in_table != state)
            {
              if (!state_in_table->it_was_placed_in_stack_for_DFA_forming)
		abort ();
              free_state (state);
              state = state_in_table;
            }
          else
            {
              if (state->it_was_placed_in_stack_for_DFA_forming)
		abort ();
              for (curr_alt_state = state->component_states;
                   curr_alt_state != NULL;
                   curr_alt_state = curr_alt_state->next_sorted_alt_state)
                for (curr_arc = first_out_arc (curr_alt_state->state);
                     curr_arc != NULL;
                     curr_arc = next_out_arc (curr_arc))
		  add_arc (state, curr_arc->to_state, curr_arc->insn, 1);
            }
          arcs_marked_by_insn->to_state = state;
          for (alts_number = 0,
	       curr_arc = arcs_marked_by_insn->next_arc_marked_by_insn;
               curr_arc != NULL;
               curr_arc = next_arc)
            {
              next_arc = curr_arc->next_arc_marked_by_insn;
              remove_arc (original_state, curr_arc);
	      alts_number++;
            }
	  arcs_marked_by_insn->state_alts = alts_number;
        }
    }
  if (!state->it_was_placed_in_stack_for_DFA_forming)
    {
      state->it_was_placed_in_stack_for_DFA_forming = 1;
      VLA_PTR_ADD (*state_stack, state);
    }
}
