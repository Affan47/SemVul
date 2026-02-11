atl1e_irq_disable(struct atl1e_adapter *adapter)
{
	AT_WRITE_REG(&adapter->hw, REG_IMR, 0);
	AT_WRITE_FLUSH(&adapter->hw);
}
