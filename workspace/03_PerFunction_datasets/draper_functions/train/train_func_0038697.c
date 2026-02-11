be_mac_setup(struct be_adapter *adapter)
{
	u8 mac[ETH_ALEN];
	int status;

	if (is_zero_ether_addr(adapter->netdev->dev_addr)) {
		status = be_cmd_get_perm_mac(adapter, mac);
		if (status)
			return status;

		memcpy(adapter->netdev->dev_addr, mac, ETH_ALEN);
		memcpy(adapter->netdev->perm_addr, mac, ETH_ALEN);
	}

	return 0;
}
