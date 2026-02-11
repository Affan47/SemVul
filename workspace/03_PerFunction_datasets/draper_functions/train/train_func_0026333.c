bfa_cb_rport_scn_online(struct bfa_s *bfa)
{
	struct bfa_fcs_s *fcs = &((struct bfad_s *)bfa->bfad)->bfa_fcs;
	struct bfa_fcs_lport_s *port = bfa_fcs_get_base_port(fcs);
	struct bfa_fcs_rport_s *rp;
	struct list_head *qe;

	list_for_each(qe, &port->rport_q) {
		rp = (struct bfa_fcs_rport_s *) qe;
		bfa_sm_send_event(rp, RPSM_EVENT_SCN_ONLINE);
		rp->scn_online = BFA_TRUE;
	}

	if (bfa_fcs_lport_is_online(port))
		bfa_fcs_lport_lip_scn_online(port);
}
