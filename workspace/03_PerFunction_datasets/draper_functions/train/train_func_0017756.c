next( const state_t &state )
{
  std::cout<<" # steps-to-go: "<<steps_to_go_<<std::endl;
  tms timenow;


  if (policy_to_use_ == RAW_WITH_MYOPIC_REPLACEMENT
      || policy_to_use_ == RAW_WITHOUT_MYOPIC_REPLACEMENT)
    {
      times(&timenow);

      if ((!hash_table_->initialized(steps_to_go_)
	   || !hash_table_->find(state, steps_to_go_)
	   || !(hash_table_->find(state, steps_to_go_)->bits() & SOLVED))
	  && elapsed_time(start_time_, timenow) <= timeout_
	  && !gpt::out_of_memory)
	{
	  solve_reverse_iter(state, steps_to_go_);
	}

      if (steps_to_go_ == problem_->horizon()
	  && hash_table_->initialized(steps_to_go_))
	{
	  hashEntry_t<double> *node = hash_table_->find(state, steps_to_go_);

	  if (node != NULL && node->bits() & SOLVED)
	    {
	      gpt::solved_completely = true;
	    }
	}
    }


  if (first_action_)
    {
      first_action_ = false;


      double valOfNormalPolicy = simulate(RAW_WITHOUT_MYOPIC_REPLACEMENT);
      std::cout<<"VALUE OF THE RAW POLICY: "<<valOfNormalPolicy<<std::endl;
      double valOfSubstPolicy = simulate(RAW_WITH_MYOPIC_REPLACEMENT);
      std::cout<<"VALUE OF THE RAW POLICY WITH REPLACEMENT OF MYOPIC ACTIONS: "
	       <<valOfSubstPolicy<<std::endl;
      std::cout<<"VALUE OF THE BEST PRIMITIVE CYCLIC POLICY: "
	       <<best_cyclic_policy_value_<<std::endl;

      if (valOfNormalPolicy >= valOfSubstPolicy
	  && valOfNormalPolicy >= best_cyclic_policy_value_)
	{
	  policy_to_use_ = RAW_WITHOUT_MYOPIC_REPLACEMENT;
	  std::cout<<"***** WILL USE THE RAW POLICY *****"<<std::endl;
	}
      else if (valOfSubstPolicy >= valOfNormalPolicy
	       && valOfSubstPolicy >= best_cyclic_policy_value_)
	{
	  policy_to_use_ = RAW_WITH_MYOPIC_REPLACEMENT;
	  std::cout<<"***** WILL USE THE RAW POLICY WITH REPLACEMENT OF MYOPIC "
		   <<"ACTIONS *****"<<std::endl;
	}
      else
	{
	  policy_to_use_ = best_cyclic_policy_;
	  std::cout<<"***** WILL USE A PRIMITIVE CYCLIC POLICY *****"
		   <<std::endl;
	}
    }


  int action = 0;

  if (policy_to_use_ == RANDOM)
    {
      action = floor(drand48()*problem_->actionsT().size());
    }
  else if (policy_to_use_ >= 0)
    {
      action = best_cyclic_policy_;
    }
  else if (policy_to_use_ == RAW_WITH_MYOPIC_REPLACEMENT)
    {
      action = next_sim(state, steps_to_go_, true);
    }
  else
    {
      action = next_sim(state, steps_to_go_, false);
    }

  assert(action >= 0 && action <= (int)problem_->actionsT().size());


  steps_to_go_--;

  if (steps_to_go_ == 0)
    {
      rounds_remaining_--;
      steps_to_go_ = problem_->horizon();
    }

  return( problem_->actionsT()[action] );
}
