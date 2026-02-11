igb_diag_test(struct net_device *netdev,
			  struct ethtool_test *eth_test, u64 *data)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	u16 autoneg_advertised;
	u8 forced_speed_duplex, autoneg;
	bool if_running = netif_running(netdev);

	set_bit(__IGB_TESTING, &adapter->state);


	if (adapter->hw.dev_spec._82575.mas_capable)
		eth_test->flags &= ~ETH_TEST_FL_OFFLINE;
	if (eth_test->flags == ETH_TEST_FL_OFFLINE) {


		autoneg_advertised = adapter->hw.phy.autoneg_advertised;
		forced_speed_duplex = adapter->hw.mac.forced_speed_duplex;
		autoneg = adapter->hw.mac.autoneg;

		dev_info(&adapter->pdev->dev, "offline testing starting\n");


		igb_power_up_link(adapter);


		if (igb_link_test(adapter, &data[TEST_LINK]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		if (if_running)

			dev_close(netdev);
		else
			igb_reset(adapter);

		if (igb_reg_test(adapter, &data[TEST_REG]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		igb_reset(adapter);
		if (igb_eeprom_test(adapter, &data[TEST_EEP]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		igb_reset(adapter);
		if (igb_intr_test(adapter, &data[TEST_IRQ]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		igb_reset(adapter);

		igb_power_up_link(adapter);
		if (igb_loopback_test(adapter, &data[TEST_LOOP]))
			eth_test->flags |= ETH_TEST_FL_FAILED;


		adapter->hw.phy.autoneg_advertised = autoneg_advertised;
		adapter->hw.mac.forced_speed_duplex = forced_speed_duplex;
		adapter->hw.mac.autoneg = autoneg;


		adapter->hw.phy.autoneg_wait_to_complete = true;
		igb_reset(adapter);
		adapter->hw.phy.autoneg_wait_to_complete = false;

		clear_bit(__IGB_TESTING, &adapter->state);
		if (if_running)
			dev_open(netdev);
	} else {
		dev_info(&adapter->pdev->dev, "online testing starting\n");


		if (if_running && igb_link_test(adapter, &data[TEST_LINK]))
			eth_test->flags |= ETH_TEST_FL_FAILED;
		else
			data[TEST_LINK] = 0;


		data[TEST_REG] = 0;
		data[TEST_EEP] = 0;
		data[TEST_IRQ] = 0;
		data[TEST_LOOP] = 0;

		clear_bit(__IGB_TESTING, &adapter->state);
	}
	msleep_interruptible(4 * 1000);
}
