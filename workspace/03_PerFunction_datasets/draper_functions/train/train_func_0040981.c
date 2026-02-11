bna_rxf_promisc_cfg_apply(struct bna_rxf *rxf)
{
	struct bna *bna = rxf->rx->bna;


	if (is_promisc_enable(rxf->rxmode_pending,
				rxf->rxmode_pending_bitmask)) {

		promisc_inactive(rxf->rxmode_pending,
				rxf->rxmode_pending_bitmask);
		rxf->rxmode_active |= BNA_RXMODE_PROMISC;
		bna_bfi_rx_promisc_req(rxf, BNA_STATUS_T_ENABLED);
		return 1;
	} else if (is_promisc_disable(rxf->rxmode_pending,
				rxf->rxmode_pending_bitmask)) {

		promisc_inactive(rxf->rxmode_pending,
				rxf->rxmode_pending_bitmask);
		rxf->rxmode_active &= ~BNA_RXMODE_PROMISC;
		bna->promisc_rid = BFI_INVALID_RID;
		bna_bfi_rx_promisc_req(rxf, BNA_STATUS_T_DISABLED);
		return 1;
	}

	return 0;
}
