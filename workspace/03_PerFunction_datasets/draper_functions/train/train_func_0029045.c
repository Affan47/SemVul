bna_rx_mod_fail(struct bna_rx_mod *rx_mod)
{
	struct bna_rx *rx;

	rx_mod->flags &= ~BNA_RX_MOD_F_ENET_STARTED;
	rx_mod->flags &= ~BNA_RX_MOD_F_ENET_LOOPBACK;

	list_for_each_entry(rx, &rx_mod->rx_active_q, qe)
		bna_rx_fail(rx);
}
