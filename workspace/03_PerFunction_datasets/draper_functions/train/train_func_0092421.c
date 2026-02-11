bfa_fcs_fabric_sm_stopping(struct bfa_fcs_fabric_s *fabric,
			   enum bfa_fcs_fabric_event event)
{
	struct bfa_s	*bfa = fabric->fcs->bfa;

	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	switch (event) {
	case BFA_FCS_FABRIC_SM_STOPCOMP:
		if (bfa_fcport_get_topology(bfa) == BFA_PORT_TOPOLOGY_LOOP) {
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_created);
		} else {
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_cleanup);
			bfa_sm_send_event(fabric->lps, BFA_LPS_SM_LOGOUT);
		}
		break;

	case BFA_FCS_FABRIC_SM_LINK_UP:
		break;

	case BFA_FCS_FABRIC_SM_LINK_DOWN:
		if (bfa_fcport_get_topology(bfa) == BFA_PORT_TOPOLOGY_LOOP)
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_created);
		else
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_cleanup);
		break;

	default:
		bfa_sm_fault(fabric->fcs, event);
	}
}
