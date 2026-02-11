igbvf_has_link(struct igbvf_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	s32 ret_val = E1000_SUCCESS;
	bool link_active;


	if (test_bit(__IGBVF_DOWN, &adapter->state))
		return false;

	ret_val = hw->mac.ops.check_for_link(hw);
	link_active = !hw->mac.get_link_status;


	if (ret_val && time_after(jiffies, adapter->last_reset + (10 * HZ)))
		schedule_work(&adapter->reset_task);

	return link_active;
}
