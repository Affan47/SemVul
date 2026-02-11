qlcnic_83xx_set_rx_tx_intr_coal(struct qlcnic_adapter *adapter)
{
	int err = 0;

	err = qlcnic_83xx_set_rx_intr_coal(adapter);
	if (err)
		netdev_err(adapter->netdev,
			   "failed to set Rx coalescing parameters\n");

	err = qlcnic_83xx_set_tx_intr_coal(adapter);
	if (err)
		netdev_err(adapter->netdev,
			   "failed to set Tx coalescing parameters\n");

	return err;
}
