bna_rxf_allmulti_cfg_apply(struct bna_rxf *rxf)
{

	if (is_allmulti_enable(rxf->rxmode_pending,
				rxf->rxmode_pending_bitmask)) {

		allmulti_inactive(rxf->rxmode_pending,
				rxf->rxmode_pending_bitmask);
		rxf->rxmode_active |= BNA_RXMODE_ALLMULTI;
		bna_bfi_mcast_filter_req(rxf, BNA_STATUS_T_DISABLED);
		return 1;
	} else if (is_allmulti_disable(rxf->rxmode_pending,
					rxf->rxmode_pending_bitmask)) {

		allmulti_inactive(rxf->rxmode_pending,
				rxf->rxmode_pending_bitmask);
		rxf->rxmode_active &= ~BNA_RXMODE_ALLMULTI;
		bna_bfi_mcast_filter_req(rxf, BNA_STATUS_T_ENABLED);
		return 1;
	}

	return 0;
}
