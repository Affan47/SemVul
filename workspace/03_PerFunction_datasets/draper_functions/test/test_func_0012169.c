incr_states_and_arcs_nums (state_t state)
{
  arc_t arc;

  curr_counted_states_num++;
  for (arc = first_out_arc (state); arc != NULL; arc = next_out_arc (arc))
    curr_counted_arcs_num++;
}
