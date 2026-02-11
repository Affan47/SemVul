failover_lease_is_better(dhcp_failover_state_t *state, struct lease *lease,
			 failover_message_t *msg)
{
	binding_state_t local_state;
	TIME msg_cltt;

	if (lease->binding_state != lease->desired_binding_state)
		local_state = lease->desired_binding_state;
	else
		local_state = lease->binding_state;

	if ((msg->options_present & FTB_CLTT) != 0)
		msg_cltt = msg->cltt;
	else
		msg_cltt = 0;

	switch(local_state) {
	      case FTS_ACTIVE:
		if (msg->binding_status == FTS_ACTIVE) {
			if (msg_cltt < lease->cltt)
				return ISC_TRUE;
			else if (msg_cltt > lease->cltt)
				return ISC_FALSE;
			else if (state->i_am == primary)
				return ISC_TRUE;
			else
				return ISC_FALSE;
		} else if (msg->binding_status == FTS_EXPIRED) {
			return ISC_FALSE;
		}


	      case FTS_FREE:
	      case FTS_BACKUP:
	      case FTS_EXPIRED:
	      case FTS_RELEASED:
	      case FTS_ABANDONED:
	      case FTS_RESET:
		if (msg->binding_status == FTS_ACTIVE)
			return ISC_FALSE;
		else if (state->i_am == primary)
			return ISC_TRUE;
		else
			return ISC_FALSE;


	      default:
		log_fatal("Impossible condition at %s:%d.", MDL);
	}

	log_fatal("Impossible condition at %s:%d.", MDL);

	return ISC_FALSE;
}
