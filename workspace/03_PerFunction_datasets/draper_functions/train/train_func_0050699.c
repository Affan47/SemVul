bna_ethport_cb_rx_stopped(struct bna_ethport *ethport)
{
	int ethport_up = ethport_is_up(ethport);

	ethport->rx_started_count--;

	if (ethport->rx_started_count == 0) {
		ethport->flags &= ~BNA_ETHPORT_F_RX_STARTED;

		if (ethport_up)
			bfa_fsm_send_event(ethport, ETHPORT_E_DOWN);
	}
}
