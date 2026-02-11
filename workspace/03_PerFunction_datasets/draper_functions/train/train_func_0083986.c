set_run_state(run state)
{
	if (conf->calc_debug & CALCDBG_RUNSTATE)
		printf("main: run_state from %s to %s\n",
			    run_state_name(run_state),
			    run_state_name(state));
	run_state = state;
}
