bna_rx_sm_quiesce_wait(struct bna_rx *rx, enum bna_rx_event event)
{
	switch (event) {
	case RX_E_STOP:
		bfa_fsm_set_state(rx, bna_rx_sm_cleanup_wait);
		break;

	case RX_E_FAIL:
		bfa_fsm_set_state(rx, bna_rx_sm_failed);
		break;

	case RX_E_CLEANUP_DONE:
		bfa_fsm_set_state(rx, bna_rx_sm_start_wait);
		break;

	default:
		bfa_sm_fault(event);
		break;
	}
}
