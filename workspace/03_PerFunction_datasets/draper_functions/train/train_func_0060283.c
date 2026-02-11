bfa_tskim_sm_cleanup(struct bfa_tskim_s *tskim, enum bfa_tskim_event event)
{
	bfa_trc(tskim->bfa, tskim->tsk_tag << 16 | event);

	switch (event) {
	case BFA_TSKIM_SM_DONE:


		break;

	case BFA_TSKIM_SM_UTAG:
	case BFA_TSKIM_SM_CLEANUP_DONE:
		bfa_sm_set_state(tskim, bfa_tskim_sm_iocleanup);
		bfa_tskim_cleanup_ios(tskim);
		break;

	case BFA_TSKIM_SM_HWFAIL:
		bfa_sm_set_state(tskim, bfa_tskim_sm_hcb);
		bfa_tskim_iocdisable_ios(tskim);
		bfa_tskim_qcomp(tskim, __bfa_cb_tskim_failed);
		break;

	default:
		bfa_sm_fault(tskim->bfa, event);
	}
}
