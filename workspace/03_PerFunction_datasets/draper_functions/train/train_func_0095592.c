wakeup_timer_fn(unsigned long data)
{
	struct mwifiex_adapter *adapter = (struct mwifiex_adapter *)data;

	mwifiex_dbg(adapter, ERROR, "Firmware wakeup failed\n");
	adapter->hw_status = MWIFIEX_HW_STATUS_RESET;
	mwifiex_cancel_all_pending_cmd(adapter);

	if (adapter->if_ops.card_reset)
		adapter->if_ops.card_reset(adapter);
}
