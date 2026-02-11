NDFA_to_DFA (automaton_t automaton)
{
  state_t start_state;
  state_t state;
  decl_t decl;
  auto_vec<state_t> state_stack;
  int i;
  int states_n;


  start_state = automaton->start_state;
  start_state->it_was_placed_in_stack_for_DFA_forming = 1;
  state_stack.safe_push (start_state);
  states_n = 1;
  while (state_stack.length () != 0)
    {
      state = state_stack.pop ();
      form_arcs_marked_by_insn (state);
      for (i = 0; i < description->decls_num; i++)
	{
	  decl = description->decls [i];
	  if (decl->mode == dm_insn_reserv
	      && decl != collapse_ndfa_insn_decl
	      && create_composed_state
	         (state, DECL_INSN_RESERV (decl)->arcs_marked_by_insn,
		  &state_stack))
	    {
	      states_n++;
	      if (progress_flag && states_n % 100 == 0)
		fprintf (stderr, ".");
	    }
	}

      if (collapse_flag)
	{
	  if (state->component_states != NULL)
	    {
	      state_t state2 = state->component_states->state;
	      if (!state2->it_was_placed_in_stack_for_DFA_forming)
		{
		  state2->it_was_placed_in_stack_for_DFA_forming = 1;
		  state_stack.safe_push (state2);
		}
	      add_arc (state, state2, automaton->collapse_ainsn);
	    }
	  else
	    add_arc (state, state, automaton->collapse_ainsn);
	}
    }
}
