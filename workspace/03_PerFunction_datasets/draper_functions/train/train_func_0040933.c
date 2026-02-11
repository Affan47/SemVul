bfa_rport_sm_created(struct bfa_rport_s *rp, enum bfa_rport_event event)
{
	bfa_trc(rp->bfa, rp->rport_tag);
	bfa_trc(rp->bfa, event);

	switch (event) {
	case BFA_RPORT_SM_ONLINE:
		bfa_stats(rp, sm_cr_on);
		if (bfa_rport_send_fwcreate(rp))
			bfa_sm_set_state(rp, bfa_rport_sm_fwcreate);
		else
			bfa_sm_set_state(rp, bfa_rport_sm_fwcreate_qfull);
		break;

	case BFA_RPORT_SM_DELETE:
		bfa_stats(rp, sm_cr_del);
		bfa_sm_set_state(rp, bfa_rport_sm_uninit);
		bfa_rport_free(rp);
		break;

	case BFA_RPORT_SM_HWFAIL:
		bfa_stats(rp, sm_cr_hwf);
		bfa_sm_set_state(rp, bfa_rport_sm_iocdisable);
		break;

	default:
		bfa_stats(rp, sm_cr_unexp);
		bfa_sm_fault(rp->bfa, event);
	}
}
