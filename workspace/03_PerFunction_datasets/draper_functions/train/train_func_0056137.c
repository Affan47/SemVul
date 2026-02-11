bfa_fcs_fabric_sm_flogi(struct bfa_fcs_fabric_s *fabric,
			enum bfa_fcs_fabric_event event)
{
	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	switch (event) {
	case BFA_FCS_FABRIC_SM_CONT_OP:

		bfa_fcport_set_tx_bbcredit(fabric->fcs->bfa,
					   fabric->bb_credit);
		fabric->fab_type = BFA_FCS_FABRIC_SWITCHED;

		if (fabric->auth_reqd && fabric->is_auth) {
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_auth);
			bfa_trc(fabric->fcs, event);
		} else {
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_online);
			bfa_fcs_fabric_notify_online(fabric);
		}
		break;

	case BFA_FCS_FABRIC_SM_RETRY_OP:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_flogi_retry);
		bfa_timer_start(fabric->fcs->bfa, &fabric->delay_timer,
				bfa_fcs_fabric_delay, fabric,
				BFA_FCS_FABRIC_RETRY_DELAY);
		break;

	case BFA_FCS_FABRIC_SM_LOOPBACK:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_loopback);
		bfa_sm_send_event(fabric->lps, BFA_LPS_SM_OFFLINE);
		bfa_fcs_fabric_set_opertype(fabric);
		break;

	case BFA_FCS_FABRIC_SM_NO_FABRIC:
		fabric->fab_type = BFA_FCS_FABRIC_N2N;
		bfa_fcport_set_tx_bbcredit(fabric->fcs->bfa,
					   fabric->bb_credit);
		bfa_fcs_fabric_notify_online(fabric);
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_nofabric);
		break;

	case BFA_FCS_FABRIC_SM_LINK_DOWN:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_linkdown);
		bfa_sm_send_event(fabric->lps, BFA_LPS_SM_OFFLINE);
		break;

	case BFA_FCS_FABRIC_SM_DELETE:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_deleting);
		bfa_sm_send_event(fabric->lps, BFA_LPS_SM_OFFLINE);
		bfa_fcs_fabric_delete(fabric);
		break;

	default:
		bfa_sm_fault(fabric->fcs, event);
	}
}
