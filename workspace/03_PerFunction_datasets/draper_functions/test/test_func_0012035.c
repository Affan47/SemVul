advance_one_cycle (void)
{
  if (targetm.sched.dfa_pre_cycle_insn)
    state_transition (curr_state,
		      targetm.sched.dfa_pre_cycle_insn ());

  state_transition (curr_state, NULL);

  if (targetm.sched.dfa_post_cycle_insn)
    state_transition (curr_state,
		      targetm.sched.dfa_post_cycle_insn ());
}
