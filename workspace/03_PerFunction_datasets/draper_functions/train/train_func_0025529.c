bfa_fcdiag_iocdisable(struct bfa_s *bfa)
{
	struct bfa_fcdiag_s *fcdiag = BFA_FCDIAG_MOD(bfa);
	struct bfa_dport_s *dport = &fcdiag->dport;

	bfa_trc(fcdiag, fcdiag->lb.lock);
	if (fcdiag->lb.lock) {
		fcdiag->lb.status = BFA_STATUS_IOC_FAILURE;
		fcdiag->lb.cbfn(fcdiag->lb.cbarg, fcdiag->lb.status);
		fcdiag->lb.lock = 0;
		bfa_fcdiag_set_busy_status(fcdiag);
	}

	bfa_sm_send_event(dport, BFA_DPORT_SM_HWFAIL);
}
