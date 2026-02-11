e1000_flush_tx_ring(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	struct e1000_ring *tx_ring = adapter->tx_ring;
	struct e1000_tx_desc *tx_desc = NULL;
	u32 tdt, tctl, txd_lower = E1000_TXD_CMD_IFCS;
	u16 size = 512;

	tctl = er32(TCTL);
	ew32(TCTL, tctl | E1000_TCTL_EN);
	tdt = er32(TDT(0));
	BUG_ON(tdt != tx_ring->next_to_use);
	tx_desc =  E1000_TX_DESC(*tx_ring, tx_ring->next_to_use);
	tx_desc->buffer_addr = tx_ring->dma;

	tx_desc->lower.data = cpu_to_le32(txd_lower | size);
	tx_desc->upper.data = 0;

	wmb();
	tx_ring->next_to_use++;
	if (tx_ring->next_to_use == tx_ring->count)
		tx_ring->next_to_use = 0;
	ew32(TDT(0), tx_ring->next_to_use);
	mmiowb();
	usleep_range(200, 250);
}
