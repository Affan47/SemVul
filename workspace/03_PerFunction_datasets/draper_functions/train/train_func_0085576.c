bfa_fcs_lport_ns_send_rspn_id(void *ns_cbarg, struct bfa_fcxp_s *fcxp_alloced)
{
	struct bfa_fcs_lport_ns_s *ns = ns_cbarg;
	struct bfa_fcs_lport_s *port = ns->port;
	struct fchs_s fchs;
	int             len;
	struct bfa_fcxp_s *fcxp;
	u8         symbl[256];
	u8         *psymbl = &symbl[0];

	memset(symbl, 0, sizeof(symbl));

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	if (!fcxp) {
		port->stats.ns_rspnid_alloc_wait++;
		bfa_fcs_fcxp_alloc_wait(port->fcs->bfa, &ns->fcxp_wqe,
				bfa_fcs_lport_ns_send_rspn_id, ns, BFA_TRUE);
		return;
	}
	ns->fcxp = fcxp;


	if (port->vport) {


		strncpy((char *)psymbl,
			(char *) &
			(bfa_fcs_lport_get_psym_name
			 (bfa_fcs_get_base_port(port->fcs))),
			strlen((char *) &
			       bfa_fcs_lport_get_psym_name(bfa_fcs_get_base_port
							  (port->fcs))));


		((char *)psymbl)[strlen((char *) &
			bfa_fcs_lport_get_psym_name(bfa_fcs_get_base_port
						(port->fcs)))] = 0;
		strncat((char *)psymbl,
			(char *) &(bfa_fcs_lport_get_psym_name(port)),
		strlen((char *) &bfa_fcs_lport_get_psym_name(port)));
	} else {
		psymbl = (u8 *) &(bfa_fcs_lport_get_psym_name(port));
	}

	len = fc_rspnid_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			      bfa_fcs_lport_get_fcid(port), 0, psymbl);

	bfa_fcxp_send(fcxp, NULL, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len, &fchs,
			  bfa_fcs_lport_ns_rspn_id_response, (void *)ns,
			  FC_MAX_PDUSZ, FC_FCCT_TOV);

	port->stats.ns_rspnid_sent++;

	bfa_sm_send_event(ns, NSSM_EVENT_RSPNID_SENT);
}
