bfa_fcs_rport_start(struct bfa_fcs_lport_s *port, struct fchs_s *fchs,
	 struct fc_logi_s *plogi)
{
	struct bfa_fcs_rport_s *rport;

	rport = bfa_fcs_rport_alloc(port, WWN_NULL, fchs->s_id);
	if (!rport)
		return;

	bfa_fcs_rport_update(rport, plogi);

	bfa_sm_send_event(rport, RPSM_EVENT_PLOGI_COMP);
}
