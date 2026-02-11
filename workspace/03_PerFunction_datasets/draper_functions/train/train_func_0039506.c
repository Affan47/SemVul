bfa_fcs_rport_sm_adisc_online(struct bfa_fcs_rport_s *rport,
				enum rport_event event)
{
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	switch (event) {
	case RPSM_EVENT_ACCEPTED:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_online);
		break;

	case RPSM_EVENT_PLOGI_RCVD:


		bfa_fcxp_discard(rport->fcxp);


	case RPSM_EVENT_FAILED:
	case RPSM_EVENT_ADDRESS_CHANGE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
		bfa_fcs_rport_hal_offline_action(rport);
		break;

	case RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logosend);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_hal_offline_action(rport);
		break;

	case RPSM_EVENT_FAB_SCN:


		break;

	case RPSM_EVENT_LOGO_IMP:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_hal_offline_action(rport);
		break;

	case RPSM_EVENT_LOGO_RCVD:
	case RPSM_EVENT_PRLO_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logorcv);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_hal_offline_action(rport);
		break;

	default:
		bfa_sm_fault(rport->fcs, event);
	}
}
