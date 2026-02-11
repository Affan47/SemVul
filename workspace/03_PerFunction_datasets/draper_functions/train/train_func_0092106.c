gate_split_functions (void)
{
  return (flag_partial_inlining
	  && !profile_arc_flag && !flag_branch_probabilities);
}
