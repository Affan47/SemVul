schedule_init(struct cardstate *cs, int state)
{
	if (cs->at_state.pending_commands & PC_INIT) {
		gig_dbg(DEBUG_EVENT, "not scheduling PC_INIT again");
		return;
	}
	cs->mstate = state;
	cs->mode = M_UNKNOWN;
	gigaset_block_channels(cs);
	cs->at_state.pending_commands |= PC_INIT;
	gig_dbg(DEBUG_EVENT, "Scheduling PC_INIT");
	cs->commands_pending = 1;
}
