bfa_fcport_sm_iocfail(struct bfa_fcport_s *fcport,
			 enum bfa_fcport_sm_event event)
{
	bfa_trc(fcport->bfa, event);

	switch (event) {
	case BFA_FCPORT_SM_START:
		bfa_sm_set_state(fcport, bfa_fcport_sm_disabled);
		break;

	case BFA_FCPORT_SM_ENABLE:
		bfa_sm_set_state(fcport, bfa_fcport_sm_iocdown);
		break;

	default:


		;
	}
}
