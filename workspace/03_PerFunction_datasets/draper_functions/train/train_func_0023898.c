ixgbevf_service_task(struct work_struct *work)
{
	struct ixgbevf_adapter *adapter = container_of(work,
						       struct ixgbevf_adapter,
						       service_task);
	struct ixgbe_hw *hw = &adapter->hw;

	if (IXGBE_REMOVED(hw->hw_addr)) {
		if (!test_bit(__IXGBEVF_DOWN, &adapter->state)) {
			rtnl_lock();
			ixgbevf_down(adapter);
			rtnl_unlock();
		}
		return;
	}

	ixgbevf_queue_reset_subtask(adapter);
	ixgbevf_reset_subtask(adapter);
	ixgbevf_watchdog_subtask(adapter);
	ixgbevf_check_hang_subtask(adapter);

	ixgbevf_service_event_complete(adapter);
}
