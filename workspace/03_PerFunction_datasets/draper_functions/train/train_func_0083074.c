atl1e_tx_queue(struct atl1e_adapter *adapter, u16 count __unused,
			   struct atl1e_tpd_desc *tpd __unused)
{
	struct atl1e_tx_ring *tx_ring = &adapter->tx_ring;
	wmb();
	AT_WRITE_REG(&adapter->hw, REG_MB_TPD_PROD_IDX, tx_ring->next_to_use);
}
