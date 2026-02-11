make_automaton (automaton_t automaton)
{
  ainsn_t ainsn;
  struct insn_reserv_decl *insn_reserv_decl;
  alt_state_t alt_state;
  state_t state;
  state_t start_state;
  state_t state2;
  ainsn_t advance_cycle_ainsn;
  arc_t added_arc;
  vla_ptr_t state_stack;
  int states_n;
  reserv_sets_t reservs_matter = form_reservs_matter (automaton);

  VLA_PTR_CREATE (state_stack, 150, "state stack");

  start_state = insert_state (get_free_state (1, automaton));
  automaton->start_state = start_state;
  start_state->it_was_placed_in_stack_for_NDFA_forming = 1;
  VLA_PTR_ADD (state_stack, start_state);
  states_n = 1;
  while (VLA_PTR_LENGTH (state_stack) != 0)
    {
      state = VLA_PTR (state_stack, VLA_PTR_LENGTH (state_stack) - 1);
      VLA_PTR_SHORTEN (state_stack, 1);
      advance_cycle_ainsn = NULL;
      for (ainsn = automaton->ainsn_list;
	   ainsn != NULL;
	   ainsn = ainsn->next_ainsn)
        if (ainsn->first_insn_with_same_reservs)
          {
            insn_reserv_decl = ainsn->insn_reserv_decl;
            if (insn_reserv_decl != DECL_INSN_RESERV (advance_cycle_insn_decl))
              {


		added_arc = NULL;
                for (alt_state = ainsn->alt_states;
                     alt_state != NULL;
                     alt_state = alt_state->next_alt_state)
                  {
                    state2 = alt_state->state;
                    if (!intersected_state_reservs_p (state, state2))
                      {
                        state2 = states_union (state, state2, reservs_matter);
                        if (!state2->it_was_placed_in_stack_for_NDFA_forming)
                          {
                            state2->it_was_placed_in_stack_for_NDFA_forming
			      = 1;
                            VLA_PTR_ADD (state_stack, state2);
			    states_n++;
			    if (progress_flag && states_n % 100 == 0)
			      fprintf (stderr, ".");
                          }
			added_arc = add_arc (state, state2, ainsn, 1);
			if (!ndfa_flag)
			  break;
                      }
                  }
		if (!ndfa_flag && added_arc != NULL)
		  {
		    added_arc->state_alts = 0;
		    for (alt_state = ainsn->alt_states;
			 alt_state != NULL;
			 alt_state = alt_state->next_alt_state)
		      {
			state2 = alt_state->state;
			if (!intersected_state_reservs_p (state, state2))
			  added_arc->state_alts++;
		      }
		  }
              }
            else
              advance_cycle_ainsn = ainsn;
          }

      state2 = state_shift (state, reservs_matter);
      if (!state2->it_was_placed_in_stack_for_NDFA_forming)
        {
          state2->it_was_placed_in_stack_for_NDFA_forming = 1;
          VLA_PTR_ADD (state_stack, state2);
	  states_n++;
	  if (progress_flag && states_n % 100 == 0)
	    fprintf (stderr, ".");
        }
      if (advance_cycle_ainsn == NULL)
	abort ();
      add_arc (state, state2, advance_cycle_ainsn, 1);
    }
  VLA_PTR_DELETE (state_stack);
}
