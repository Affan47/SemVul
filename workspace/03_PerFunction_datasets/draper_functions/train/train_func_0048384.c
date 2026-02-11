e1000_flush_desc_rings(struct e1000_adapter *adapter)
{
	u16 hang_state;
	u32 fext_nvm11, tdlen;
	struct e1000_hw *hw = &adapter->hw;


	fext_nvm11 = er32(FEXTNVM11);
	fext_nvm11 |= E1000_FEXTNVM11_DISABLE_MULR_FIX;
	ew32(FEXTNVM11, fext_nvm11);

	tdlen = er32(TDLEN(0));
	pci_read_config_word(adapter->pdev, PCICFG_DESC_RING_STATUS,
			     &hang_state);
	if (!(hang_state & FLUSH_DESC_REQUIRED) || !tdlen)
		return;
	e1000_flush_tx_ring(adapter);

	pci_read_config_word(adapter->pdev, PCICFG_DESC_RING_STATUS,
			     &hang_state);
	if (hang_state & FLUSH_DESC_REQUIRED)
		e1000_flush_rx_ring(adapter);
}
