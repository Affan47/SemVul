bna_tx_sm_prio_stop_wait(struct bna_tx *tx, enum bna_tx_event event)
{
	switch (event) {
	case TX_E_STOP:
		bfa_fsm_set_state(tx, bna_tx_sm_stop_wait);
		break;

	case TX_E_FAIL:
		bfa_fsm_set_state(tx, bna_tx_sm_failed);
		tx->tx_cleanup_cbfn(tx->bna->bnad, tx);
		break;

	case TX_E_STOPPED:
		bfa_fsm_set_state(tx, bna_tx_sm_prio_cleanup_wait);
		break;

	case TX_E_BW_UPDATE:

		break;

	default:
		bfa_sm_fault(event);
	}
}
