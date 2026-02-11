compute_function_frequency ()
{
  basic_block bb;

  if (!profile_info.count_profiles_merged
      || !flag_branch_probabilities)
    return;
  cfun->function_frequency = FUNCTION_FREQUENCY_UNLIKELY_EXECUTED;
  FOR_EACH_BB (bb)
    {
      if (maybe_hot_bb_p (bb))
	{
	  cfun->function_frequency = FUNCTION_FREQUENCY_HOT;
	  return;
	}
      if (!probably_never_executed_bb_p (bb))
	cfun->function_frequency = FUNCTION_FREQUENCY_NORMAL;
    }
}
