longest_path_length (state)
     state_t state;
{
  arc_t arc;
  int length, result;

  if (state->longest_path_length == ON_THE_PATH)


    abort ();
  else if (state->longest_path_length != UNDEFINED_LONGEST_PATH_LENGTH)

    return state->longest_path_length;

  result = 0;
  for (arc = first_out_arc (state); arc != NULL; arc = next_out_arc (arc))

    if (arc->to_state != state
	&& (arc->insn->insn_reserv_decl
	    != DECL_INSN_RESERV (advance_cycle_insn_decl)))
    {
      length = longest_path_length (arc->to_state);
      if (length > result)
	result = length;
    }
  state->longest_path_length = result + 1;
  return result;
}
