handle_icall(struct cardstate *cs, struct bc_state *bcs,
			 struct at_state_t *at_state)
{
	int retval;

	retval = gigaset_isdn_icall(at_state);
	switch (retval) {
	case ICALL_ACCEPT:
		break;
	default:
		dev_err(cs->dev, "internal error: disposition=%d\n", retval);

	case ICALL_IGNORE:
	case ICALL_REJECT:


		at_state->pending_commands |= PC_HUP;
		cs->commands_pending = 1;
		break;
	}
}
