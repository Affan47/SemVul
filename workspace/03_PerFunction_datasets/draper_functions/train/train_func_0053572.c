bfa_tskim_sm_hcb(struct bfa_tskim_s *tskim, enum bfa_tskim_event event)
{
	bfa_trc(tskim->bfa, tskim->tsk_tag << 16 | event);

	switch (event) {
	case BFA_TSKIM_SM_HCB:
		bfa_sm_set_state(tskim, bfa_tskim_sm_uninit);
		bfa_tskim_free(tskim);
		break;

	case BFA_TSKIM_SM_CLEANUP:
		bfa_tskim_notify_comp(tskim);
		break;

	case BFA_TSKIM_SM_HWFAIL:
		break;

	default:
		bfa_sm_fault(tskim->bfa, event);
	}
}
