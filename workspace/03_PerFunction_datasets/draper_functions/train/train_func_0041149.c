bfa_fcs_lport_ns_gid_ft_response(void *fcsarg, struct bfa_fcxp_s *fcxp,
				void *cbarg, bfa_status_t req_status,
				u32 rsp_len, u32 resid_len,
				struct fchs_s *rsp_fchs)
{
	struct bfa_fcs_lport_ns_s *ns = (struct bfa_fcs_lport_ns_s *) cbarg;
	struct bfa_fcs_lport_s *port = ns->port;
	struct ct_hdr_s *cthdr = NULL;
	u32        n_pids;

	bfa_trc(port->fcs, port->port_cfg.pwwn);


	if (req_status != BFA_STATUS_OK) {
		bfa_trc(port->fcs, req_status);
		port->stats.ns_gidft_rsp_err++;
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
		return;
	}

	if (resid_len != 0) {


		bfa_trc(port->fcs, rsp_len);
		bfa_trc(port->fcs, resid_len);
		return;
	}

	cthdr = (struct ct_hdr_s *) BFA_FCXP_RSP_PLD(fcxp);
	cthdr->cmd_rsp_code = be16_to_cpu(cthdr->cmd_rsp_code);

	switch (cthdr->cmd_rsp_code) {

	case CT_RSP_ACCEPT:

		port->stats.ns_gidft_accepts++;
		n_pids = (fc_get_ctresp_pyld_len(rsp_len) / sizeof(u32));
		bfa_trc(port->fcs, n_pids);
		bfa_fcs_lport_ns_process_gidft_pids(port,
						   (u32 *) (cthdr + 1),
						   n_pids);
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_OK);
		break;

	case CT_RSP_REJECT:


		port->stats.ns_gidft_rejects++;
		bfa_trc(port->fcs, cthdr->reason_code);
		bfa_trc(port->fcs, cthdr->exp_code);

		if ((cthdr->reason_code == CT_RSN_UNABLE_TO_PERF)
		    && (cthdr->exp_code == CT_NS_EXP_FT_NOT_REG)) {

			bfa_sm_send_event(ns, NSSM_EVENT_RSP_OK);
		} else {


			bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
		}
		break;

	default:
		port->stats.ns_gidft_unknown_rsp++;
		bfa_trc(port->fcs, cthdr->cmd_rsp_code);
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
	}
}
