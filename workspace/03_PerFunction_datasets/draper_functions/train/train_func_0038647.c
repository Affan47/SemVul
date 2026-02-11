ixgbe_set_phys_id(struct net_device *netdev,
			     enum ethtool_phys_id_state state)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	struct ixgbe_hw *hw = &adapter->hw;

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		adapter->led_reg = IXGBE_READ_REG(hw, IXGBE_LEDCTL);
		return 2;

	case ETHTOOL_ID_ON:
		hw->mac.ops.led_on(hw, IXGBE_LED_ON);
		break;

	case ETHTOOL_ID_OFF:
		hw->mac.ops.led_off(hw, IXGBE_LED_ON);
		break;

	case ETHTOOL_ID_INACTIVE:

		IXGBE_WRITE_REG(&adapter->hw, IXGBE_LEDCTL, adapter->led_reg);
		break;
	}

	return 0;
}
