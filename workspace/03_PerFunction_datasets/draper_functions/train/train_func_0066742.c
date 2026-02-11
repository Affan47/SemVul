et1310_config_flow_control(struct et131x_adapter *adapter)
{
	struct phy_device *phydev = adapter->phydev;

	if (phydev->duplex == DUPLEX_HALF) {
		adapter->flow = FLOW_NONE;
	} else {
		char remote_pause, remote_async_pause;

		et1310_phy_read_mii_bit(adapter, 5, 10, &remote_pause);
		et1310_phy_read_mii_bit(adapter, 5, 11, &remote_async_pause);

		if (remote_pause && remote_async_pause) {
			adapter->flow = adapter->wanted_flow;
		} else if (remote_pause && !remote_async_pause) {
			if (adapter->wanted_flow == FLOW_BOTH)
				adapter->flow = FLOW_BOTH;
			else
				adapter->flow = FLOW_NONE;
		} else if (!remote_pause && !remote_async_pause) {
			adapter->flow = FLOW_NONE;
		} else {
			if (adapter->wanted_flow == FLOW_BOTH)
				adapter->flow = FLOW_RXONLY;
			else
				adapter->flow = FLOW_NONE;
		}
	}
}
