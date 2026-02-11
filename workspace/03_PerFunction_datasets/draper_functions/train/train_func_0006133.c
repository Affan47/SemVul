create_live_range_start_chains (void)
{
  int i, max_regno;
  lra_live_range_t r;

  start_point_ranges = XCNEWVEC (lra_live_range_t, lra_live_max_point);
  max_regno = max_reg_num ();
  for (i = FIRST_PSEUDO_REGISTER; i < max_regno; i++)
    if (i >= lra_constraint_new_regno_start || reg_renumber[i] >= 0)
      {
	for (r = lra_reg_info[i].live_ranges; r != NULL; r = r->next)
	  {
	    r->start_next = start_point_ranges[r->start];
	    start_point_ranges[r->start] = r;
	  }
      }
    else
      {
	for (r = lra_reg_info[i].live_ranges; r != NULL; r = r->next)
	  r->start_next = &not_in_chain_mark;
      }
}
