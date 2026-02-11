bfa_fcs_rport_plogi_create(struct bfa_fcs_lport_s *port, struct fchs_s *fchs,
				struct fc_logi_s *plogi)
{
	struct bfa_fcs_rport_s *rport;

	rport = bfa_fcs_rport_alloc(port, plogi->port_name, fchs->s_id);
	if (!rport)
		return;

	bfa_fcs_rport_update(rport, plogi);

	rport->reply_oxid = fchs->ox_id;
	bfa_trc(rport->fcs, rport->reply_oxid);

	rport->stats.plogi_rcvd++;
	bfa_sm_send_event(rport, RPSM_EVENT_PLOGI_RCVD);
}
