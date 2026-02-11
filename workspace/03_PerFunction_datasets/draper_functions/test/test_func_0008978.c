ixgbe_ptp_init(struct ixgbe_adapter *adapter)
{


	spin_lock_init(&adapter->tmreg_lock);


	if (ixgbe_ptp_create_clock(adapter))
		return;


	INIT_WORK(&adapter->ptp_tx_work, ixgbe_ptp_tx_hwtstamp_work);


	ixgbe_ptp_reset(adapter);


	set_bit(__IXGBE_PTP_RUNNING, &adapter->state);

	return;
}
