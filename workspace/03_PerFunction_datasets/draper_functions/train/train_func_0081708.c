bna_rx_vlan_add(struct bna_rx *rx, int vlan_id)
{
	struct bna_rxf *rxf = &rx->rxf;
	int index = (vlan_id >> BFI_VLAN_WORD_SHIFT);
	int bit = BIT(vlan_id & BFI_VLAN_WORD_MASK);
	int group_id = (vlan_id >> BFI_VLAN_BLOCK_SHIFT);

	rxf->vlan_filter_table[index] |= bit;
	if (rxf->vlan_filter_status == BNA_STATUS_T_ENABLED) {
		rxf->vlan_pending_bitmask |= BIT(group_id);
		bfa_fsm_send_event(rxf, RXF_E_CONFIG);
	}
}
