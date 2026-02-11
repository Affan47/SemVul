test_timeout(struct at_state_t *at_state)
{
	if (!at_state->timer_expires)
		return 0;

	if (--at_state->timer_expires) {
		gig_dbg(DEBUG_MCMD, "decreased timer of %p to %lu",
			at_state, at_state->timer_expires);
		return 0;
	}

	gigaset_add_event(at_state->cs, at_state, EV_TIMEOUT, NULL,
			  at_state->timer_index, NULL);
	return 1;
}
