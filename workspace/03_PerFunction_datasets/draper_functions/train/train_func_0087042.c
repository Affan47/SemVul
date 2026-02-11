bfa_dport_req_comp(struct bfa_dport_s *dport, struct bfi_diag_dport_rsp_s *msg)
{
	msg->status = cpu_to_be32(msg->status);
	dport->i2hmsg.rsp.status = msg->status;
	dport->rp_pwwn = msg->pwwn;
	dport->rp_nwwn = msg->nwwn;

	if ((msg->status == BFA_STATUS_OK) ||
	    (msg->status == BFA_STATUS_DPORT_NO_SFP)) {
		bfa_trc(dport->bfa, msg->status);
		bfa_trc(dport->bfa, dport->rp_pwwn);
		bfa_trc(dport->bfa, dport->rp_nwwn);
		bfa_sm_send_event(dport, BFA_DPORT_SM_FWRSP);

	} else {
		bfa_trc(dport->bfa, msg->status);
		bfa_sm_send_event(dport, BFA_DPORT_SM_REQFAIL);
	}
	bfa_cb_fcdiag_dport(dport, msg->status);
}
