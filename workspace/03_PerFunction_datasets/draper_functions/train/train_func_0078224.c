ixgbe_sfp_link_config_subtask(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 speed;
	bool autoneg = false;

	if (!(adapter->flags & IXGBE_FLAG_NEED_LINK_CONFIG))
		return;


	if (test_and_set_bit(__IXGBE_IN_SFP_INIT, &adapter->state))
		return;

	adapter->flags &= ~IXGBE_FLAG_NEED_LINK_CONFIG;

	speed = hw->phy.autoneg_advertised;
	if ((!speed) && (hw->mac.ops.get_link_capabilities)) {
		hw->mac.ops.get_link_capabilities(hw, &speed, &autoneg);


		if (!autoneg) {
			if (speed & IXGBE_LINK_SPEED_10GB_FULL)
				speed = IXGBE_LINK_SPEED_10GB_FULL;
		}
	}

	if (hw->mac.ops.setup_link)
		hw->mac.ops.setup_link(hw, speed, true);

	adapter->flags |= IXGBE_FLAG_NEED_LINK_UPDATE;
	adapter->link_check_timeout = jiffies;
	clear_bit(__IXGBE_IN_SFP_INIT, &adapter->state);
}
