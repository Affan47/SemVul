bfa_fcs_lport_ns_rff_id_response(void *fcsarg, struct bfa_fcxp_s *fcxp,
				void *cbarg, bfa_status_t req_status,
				u32 rsp_len, u32 resid_len,
				struct fchs_s *rsp_fchs)
{
	struct bfa_fcs_lport_ns_s *ns = (struct bfa_fcs_lport_ns_s *) cbarg;
	struct bfa_fcs_lport_s *port = ns->port;
	struct ct_hdr_s *cthdr = NULL;

	bfa_trc(port->fcs, port->port_cfg.pwwn);


	if (req_status != BFA_STATUS_OK) {
		bfa_trc(port->fcs, req_status);
		port->stats.ns_rffid_rsp_err++;
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
		return;
	}

	cthdr = (struct ct_hdr_s *) BFA_FCXP_RSP_PLD(fcxp);
	cthdr->cmd_rsp_code = be16_to_cpu(cthdr->cmd_rsp_code);

	if (cthdr->cmd_rsp_code == CT_RSP_ACCEPT) {
		port->stats.ns_rffid_accepts++;
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_OK);
		return;
	}

	port->stats.ns_rffid_rejects++;
	bfa_trc(port->fcs, cthdr->reason_code);
	bfa_trc(port->fcs, cthdr->exp_code);

	if (cthdr->reason_code == CT_RSN_NOT_SUPP) {

		bfa_sm_send_event(ns, NSSM_EVENT_RSP_OK);
	} else
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
}
