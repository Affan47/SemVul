ixgbe_ptp_suspend(struct ixgbe_adapter *adapter)
{

	if (!test_and_clear_bit(__IXGBE_PTP_RUNNING, &adapter->state))
		return;

	adapter->flags2 &= ~IXGBE_FLAG2_PTP_PPS_ENABLED;
	if (adapter->ptp_setup_sdp)
		adapter->ptp_setup_sdp(adapter);


	cancel_work_sync(&adapter->ptp_tx_work);
	ixgbe_ptp_clear_tx_timestamp(adapter);
}
