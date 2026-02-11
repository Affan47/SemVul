push_to_next_round_p (const_basic_block bb, int round, int number_of_rounds,
		      int exec_th, gcov_type count_th)
{
  bool there_exists_another_round;
  bool block_not_hot_enough;

  there_exists_another_round = round < number_of_rounds - 1;

  block_not_hot_enough = (bb->frequency < exec_th
			  || bb->count < count_th
			  || probably_never_executed_bb_p (cfun, bb));

  if (there_exists_another_round
      && block_not_hot_enough)
    return true;
  else
    return false;
}
